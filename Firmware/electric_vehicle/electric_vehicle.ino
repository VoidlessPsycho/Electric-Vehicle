// ============================================================
//  Science Olympiad Electric Vehicle Controller
//  Hardware : ESP32 DevKit V1, TB6612FNG, 2x N20 1:30 6V
//             360 PPR encoders (after gearbox), 9V battery
// ============================================================

// ─── Pin Definitions ────────────────────────────────────────
#define AIN1 32
#define AIN2 33
#define PWMA 25
#define BIN1 26
#define BIN2 27
#define PWMB 14
#define STBY 13

#define LEFT_ENC_A  19
#define LEFT_ENC_B  18
#define RIGHT_ENC_A 17
#define RIGHT_ENC_B 16

#define StartButton 4

// ─── LEDC (PWM) channels ────────────────────────────────────
#define LEDC_A    0
#define LEDC_B    1
#define LEDC_FREQ 20000
#define LEDC_RES  8       // 8-bit → 0–255

// ─── Physical Constants ─────────────────────────────────────
#define ENCODER_PPR      179.16f   // pulses per rev after gearbox
#define WHEEL_DIAM_MM     41.275f   // *** measure your wheel ***
#define WHEEL_BASE_MM    44.3f   // *** centre-to-centre ***

#define MM_PER_REV        (PI * WHEEL_DIAM_MM)
#define COUNTS_PER_MM     (ENCODER_PPR / MM_PER_REV)

// ─── Gains  (tune in order: KFF → KSP → KDP → KSI → KDI → KST) ────────
//
//  KFF : feedforward scale on speedProfile
//        Start ~1.0, adjust until motor roughly tracks open-loop
//  KSP : proportional on S_Error (speed error)
//  KDP : proportional on D_Error (distance error)
//  KSI : integral on S_Error — eliminates steady-state speed offset
//        Start ~0.0, increase slowly; too large causes oscillation
//  KDI : integral on D_Error — eliminates steady-state distance offset
//        Start ~0.0, increase slowly; too large causes overshoot
//  KST : proportional on steering error (straight segments only)
//
float KFF = 0.5f;   // was 0.7
float KSP = 0.8f;   // was 0.5 — more speed correction
float KDP = 1.2f;   // was 0.8 — more distance correction
float KST = 2.1f;

// ─── Integral windup limit (counts/s equivalent) ────────────
// Prevents integral from growing unbounded during long errors.
// Set to ~20–30% of MAX_SPEED as a starting point.
#define INTEGRAL_LIMIT 80.0f   // tighter — prevents windup fighting battery sag
float KSI = 0.02f;  // back off integral — it's making things worse on weak batteries
float KDI = 0.05f;

// ─── Motion Profile Parameters ──────────────────────────────
float ACCEL_RATE = 1500.0f;    // counts/s²
float DECEL_RATE = 1500.0f;    // counts/s²
float MAX_SPEED  = 1500.0f;   // counts/s — set to measured free-run speed

// ─── Sequence ───────────────────────────────────────────────
// curveDelta = extra counts outer wheel travels vs inner
//   > 0 → right turn,  < 0 → left turn
struct Segment {
  float distanceMM;
  float curveDelta;
  bool  isCurve;
};

// ─── Start Delay ─────────────────────────────────────────────
float START_DELAY_MS = 0.0f;  // *** change this to your desired delay ***
const float trackLen = 0.0f;
const float startEndDist = ((trackLen - 7.0)/2)*1000.0;

// *** EDIT THIS to match your course ***
const Segment SEQUENCE[] = {
  {startEndDist, 0.0, false},
  {1800.0, 0.0, false},
  {800.0, -480.0, true},
  {1200.0, 550.0, true},
  {1350.0, 0.0, false},
  {850.0, 500.0, true},
  {1100.0, -200.0, true},
  {2800.0, 0.0, false},
  {startEndDist, 0.0, false}
};
const int NUM_SEGMENTS = sizeof(SEQUENCE) / sizeof(SEQUENCE[0]);

// ─── Encoder Counts (ISR-updated) ───────────────────────────
volatile long leftCount  = 0;
volatile long rightCount = 0;

// ─── Per-segment state ──────────────────────────────────────
int   segIndex       = 0;
long  segStartLeft   = 0;
long  segStartRight  = 0;
long  segStartTime_us = 0;

// Trapezoidal profile timing (absolute microseconds from segment start)
long  timeEndAccel_us = 0;
long  timeEndConst_us = 0;
long  timeEndDecel_us = 0;

float segMaxSpeed       = 0.0f;
float segTargetCounts   = 0.0f;
float leftTargetCounts  = 0.0f;
float rightTargetCounts = 0.0f;

bool  running = false;

// ─── Integral accumulators (reset each segment) ─────────────
float leftIntegral  = 0.0f;   // ← NEW
float rightIntegral = 0.0f;   // ← NEW

// ─── Control loop timing ────────────────────────────────────
long  prevTime_us    = 0;
long  prevLeftCount  = 0;
long  prevRightCount = 0;

// ═══════════════════════════════════════════════════════════
//  ENCODER ISRs
// ═══════════════════════════════════════════════════════════
void IRAM_ATTR leftEncA_ISR() {
  if (digitalRead(LEFT_ENC_A) == digitalRead(LEFT_ENC_B)) leftCount++;
  else leftCount--;
}
void IRAM_ATTR rightEncA_ISR() {
  if (digitalRead(RIGHT_ENC_A) == digitalRead(RIGHT_ENC_B)) rightCount++;
  else rightCount--;
}

// ═══════════════════════════════════════════════════════════
//  MOTOR DRIVER
// ═══════════════════════════════════════════════════════════
void setMotorA(int pwm) {
  pwm = constrain(pwm, -255, 255);
  if (pwm >= 0) { digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);  }
  else          { digitalWrite(AIN1, LOW);  digitalWrite(AIN2, HIGH); pwm = -pwm; }
  ledcWrite(PWMA, pwm);
}
void setMotorB(int pwm) {
  pwm = constrain(pwm, -255, 255);
  if (pwm >= 0) { digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);  }
  else          { digitalWrite(BIN1, LOW);  digitalWrite(BIN2, HIGH); pwm = -pwm; }
  ledcWrite(PWMB, pwm);
}
void stopMotors() {
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, LOW); ledcWrite(PWMA, 0);
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, LOW); ledcWrite(PWMB, 0);
}

// ═══════════════════════════════════════════════════════════
//  TRAPEZOIDAL PROFILE
//
//  speedProfile(t)  →  S_Profile  [counts/s]
//  distProfile(t)   →  D_Profile  [counts]   via d = v0*t + 0.5*a*t²
//
//  Both are functions of elapsed microseconds since segment start.
// ═══════════════════════════════════════════════════════════
float speedProfile(long t_us) {
  float t  = t_us * 1e-6f;
  float tA =  timeEndAccel_us                         * 1e-6f;
  float tC = (timeEndConst_us - timeEndAccel_us)      * 1e-6f;
  float tD = (timeEndDecel_us - timeEndConst_us)      * 1e-6f;

  if (t <= 0.0f)           return 0.0f;
  if (t <= tA)             return ACCEL_RATE * t;
  if (t <= tA + tC)        return segMaxSpeed;
  if (t <= tA + tC + tD)   return segMaxSpeed - DECEL_RATE * (t - tA - tC);
  return 0.0f;
}

float distProfile(long t_us) {
  float t  = t_us * 1e-6f;
  float tA =  timeEndAccel_us                         * 1e-6f;
  float tC = (timeEndConst_us - timeEndAccel_us)      * 1e-6f;
  float tD = (timeEndDecel_us - timeEndConst_us)      * 1e-6f;

  float dA = 0.5f * ACCEL_RATE * tA * tA;
  float dC = segMaxSpeed * tC;

  if (t <= 0.0f)           return 0.0f;
  if (t <= tA)             return 0.5f * ACCEL_RATE * t * t;
  if (t <= tA + tC)        return dA + segMaxSpeed * (t - tA);
  if (t <= tA + tC + tD) {
    float td = t - tA - tC;
    return dA + dC + segMaxSpeed * td - 0.5f * DECEL_RATE * td * td;
  }
  return dA + dC + (segMaxSpeed * tD - 0.5f * DECEL_RATE * tD * tD);
}

// ═══════════════════════════════════════════════════════════
//  SEGMENT SETUP
// ═══════════════════════════════════════════════════════════
void startSegment(int idx) {
  const Segment &s = SEQUENCE[idx];

  segStartLeft    = leftCount;
  segStartRight   = rightCount;
  segStartTime_us = micros();

  // Reset integral accumulators on each new segment               ← NEW
  leftIntegral  = 0.0f;                                           // ← NEW
  rightIntegral = 0.0f;                                           // ← NEW

  // Per-wheel target counts
  float avgCounts = s.distanceMM * COUNTS_PER_MM;
  leftTargetCounts  = avgCounts + (s.isCurve ?  s.curveDelta * 0.5f : 0.0f);
  rightTargetCounts = avgCounts + (s.isCurve ? -s.curveDelta * 0.5f : 0.0f);
  segTargetCounts   = avgCounts;

  // Peak speed capped for short moves
  segMaxSpeed = min(MAX_SPEED, sqrtf(ACCEL_RATE * segTargetCounts));

  float tA = segMaxSpeed / ACCEL_RATE;
  float tD = segMaxSpeed / DECEL_RATE;
  float dA = 0.5f * ACCEL_RATE * tA * tA;
  float dD = segMaxSpeed * tD - 0.5f * DECEL_RATE * tD * tD;
  float distConst = segTargetCounts - dA - dD;

  if (distConst < 0.0f) {
    // Triangular profile — no constant-speed phase
    segMaxSpeed = sqrtf(segTargetCounts * ACCEL_RATE * DECEL_RATE
                        / (ACCEL_RATE + DECEL_RATE));
    tA = segMaxSpeed / ACCEL_RATE;
    tD = segMaxSpeed / DECEL_RATE;
    distConst = 0.0f;
  }

  float tC = (segMaxSpeed > 0.0f) ? distConst / segMaxSpeed : 0.0f;

  timeEndAccel_us = (long)(tA * 1e6f);
  timeEndConst_us = timeEndAccel_us + (long)(tC * 1e6f);
  timeEndDecel_us = timeEndConst_us + (long)(tD * 1e6f);
}

// ═══════════════════════════════════════════════════════════
//  CONTROL LOOP — called every ~5 ms
//
//  Diagram implementation (now with integral term):
//
//    S_Error = speedProfile(t) − speedActual       [counts/s]
//    D_Error = distProfile(t)  − distActual        [counts]
//
//    P   = KSP * S_Error  +  KDP * D_Error
//    I   = I_Last + KSI * S_Error + KDI * D_Error  ← NEW
//    FF  = KFF * speedProfile(t)
//    PWM = P + I + FF
// ═══════════════════════════════════════════════════════════
void controlLoop() {
  if (!running) return;

  long now_us = micros();
  float dt = (now_us - prevTime_us) * 1e-6f;
  if (dt < 0.001f) return;

  // ── 1. Snapshot encoders ────────────────────────────────
  long lc = leftCount;
  long rc = rightCount;

  // ── 2. Actual speed  [counts/s] ─────────────────────────
  // Replace the two speed lines with a low-pass filter
  static float leftSpeedFilt  = 0.0f;
  static float rightSpeedFilt = 0.0f;
  float alpha = 0.4f;  // 0=frozen, 1=raw — tune between 0.3–0.6
  leftSpeedFilt  = alpha * ((lc - prevLeftCount) / dt) + (1.0f - alpha) * leftSpeedFilt;
  rightSpeedFilt = alpha * ((rc - prevRightCount) / dt) + (1.0f - alpha) * rightSpeedFilt;
  float leftSpeedActual  = leftSpeedFilt;
  float rightSpeedActual = rightSpeedFilt;
  prevLeftCount  = lc;
  prevRightCount = rc;
  prevTime_us    = now_us;

  // ── 3. Elapsed time in segment ──────────────────────────
  long t_us = now_us - segStartTime_us;

  // ── 4. Profile values for average wheel ─────────────────
  float sProfile = speedProfile(t_us);   // S_Profile [counts/s]
  float dProfile = distProfile(t_us);    // D_Profile [counts]

  // ── 5. Scale profiles to each wheel (curve support) ─────
  float leftSProfile  = sProfile;
  float rightSProfile = sProfile;
  float leftDProfile  = dProfile;
  float rightDProfile = dProfile;

  if (SEQUENCE[segIndex].isCurve && segTargetCounts > 0.0f) {
    float lRatio = leftTargetCounts  / segTargetCounts;
    float rRatio = rightTargetCounts / segTargetCounts;
    leftSProfile  = sProfile * lRatio;
    rightSProfile = sProfile * rRatio;
    leftDProfile  = dProfile * lRatio;
    rightDProfile = dProfile * rRatio;
  }

  // ── 6. Actual distance this segment [counts] ────────────
  float leftDistActual  = (float)(lc - segStartLeft);
  float rightDistActual = (float)(rc - segStartRight);

  // ── 7. S_Error and D_Error (diagram signal names) ───────
  float leftSError  = leftSProfile  - leftSpeedActual;
  float rightSError = rightSProfile - rightSpeedActual;

  float leftDError  = leftDProfile  - leftDistActual;
  float rightDError = rightDProfile - rightDistActual;

  // ── 8. P = KSP * S_Error  +  KDP * D_Error ─────────────
  float leftP  = KSP * leftSError  + KDP * leftDError;
  float rightP = KSP * rightSError + KDP * rightDError;

  // ── 9. I = I_Last + KSI * S_Error + KDI * D_Error ──────  ← NEW
  //         (anti-windup: clamp accumulator to ±INTEGRAL_LIMIT)
  leftIntegral  = constrain(leftIntegral  + KSI * leftSError  + KDI * leftDError,
                            -INTEGRAL_LIMIT, INTEGRAL_LIMIT);
  rightIntegral = constrain(rightIntegral + KSI * rightSError + KDI * rightDError,
                            -INTEGRAL_LIMIT, INTEGRAL_LIMIT);

  // ── 10. FF = KFF * speedProfile ─────────────────────────
  float leftFF  = KFF * leftSProfile;
  float rightFF = KFF * rightSProfile;

  // ── 11. PWM = P + I + FF ────────────────────────────────  ← NEW (added I)
  float leftOut  = leftP  + leftIntegral  + leftFF;
  float rightOut = rightP + rightIntegral + rightFF;

  // ── 12. Steering correction (straight segments only) ────
  if (!SEQUENCE[segIndex].isCurve) {
    float steerError = leftDistActual - rightDistActual;
    leftOut  -= KST * steerError;
    rightOut += KST * steerError;
  }

  // ── 13. Drive motors ────────────────────────────────────
  float pwmScale = 255.0f / MAX_SPEED;
  setMotorA((int)(leftOut  * pwmScale));
  setMotorB((int)(rightOut * pwmScale));

  // ── 14. Serial Plotter output ───────────────────────────
  // Plot 1: Speed tracking
  Serial.printf("sPro:%.1f lSpd:%.1f rSpd:%.1f lSErr:%.1f rSErr:%.1f dPro:%.1f lDst:%.1f rDst:%.1f lDErr:%.1f rDErr:%.1f lInt:%.1f rInt:%.1f lP:%.1f rP:%.1f\n",
    sProfile, leftSpeedActual, rightSpeedActual, leftSError, rightSError, dProfile, leftDistActual, rightDistActual, leftDError, rightDError, leftIntegral, rightIntegral, leftP, rightP);

  // Plot 2: Distance tracking (comment Plot 1, uncomment this)
  // Serial.printf("dPro:%.1f lDst:%.1f rDst:%.1f lDErr:%.1f rDErr:%.1f\n",
  //   dProfile, leftDistActual, rightDistActual, leftDError, rightDError);

  // Plot 3: Integral terms (comment others, uncomment this)   ← NEW
  // Serial.printf("lInt:%.1f rInt:%.1f lP:%.1f rP:%.1f\n",
  //   leftIntegral, rightIntegral, leftP, rightP);

  // ── 15. Segment complete check ───────────────────────────
  float avgDistActual = (leftDistActual + rightDistActual) * 0.5f;
  bool  timeUp   = (t_us > timeEndDecel_us + 150000L);
  bool distDone = (avgDistActual >= segTargetCounts * 0.99f)
             && (t_us >= timeEndDecel_us);

  if (timeUp || distDone) {
    segIndex++;
    if (segIndex >= NUM_SEGMENTS) {
      stopMotors();
      running = false;
      Serial.println("=== SEQUENCE COMPLETE ===");
    } else {
      startSegment(segIndex);
    }
  }
}

// ═══════════════════════════════════════════════════════════
//  SETUP
// ═══════════════════════════════════════════════════════════
void setup() {
  Serial.begin(115200);

  pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT); digitalWrite(STBY, HIGH);

  ledcAttach(PWMA, LEDC_FREQ, LEDC_RES);
  ledcAttach(PWMB, LEDC_FREQ, LEDC_RES);
  stopMotors();

  pinMode(LEFT_ENC_A,  INPUT_PULLUP); pinMode(LEFT_ENC_B,  INPUT_PULLUP);
  pinMode(RIGHT_ENC_A, INPUT_PULLUP); pinMode(RIGHT_ENC_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENC_A),  leftEncA_ISR,  CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENC_A), rightEncA_ISR, CHANGE);

  pinMode(StartButton, INPUT_PULLUP);
  Serial.println("Ready — press button to start.");
}

// ═══════════════════════════════════════════════════════════
//  LOOP
// ═══════════════════════════════════════════════════════════
static bool lastBtn = HIGH;

void loop() {
  bool btn = digitalRead(StartButton);

  if (lastBtn == HIGH && btn == LOW && !running) {
    delay(20);
    delay((int)START_DELAY_MS);  // ← add this line
    leftCount = 0; rightCount = 0;
    segIndex  = 0;
    prevLeftCount = 0; prevRightCount = 0;
    prevTime_us   = micros();
    running = true;
    startSegment(0);
    Serial.println("=== SEQUENCE START ===");
  }
  lastBtn = btn;

  controlLoop();
  delay(5);
}
