# Journal

### September 10, 2025: Analyzing Rules
I read through the guidelines for the Electric Vehicle event to figure out exactly what I had to do. The rules also included constraints on what I cannot do, such as limiting power to a maximum of 8 x AA Batteries for max of 12 V. \
The challenge requires the vehicle to go from the start point to the end point in a set amount of time. For bonus points, it can go through a gap made by cans to the left. This track is illustrated in the image below: \
![image](https://cdn.hackclub.com/019f0781-6d3c-787d-8302-4fe18f92263a/9-10-25.png)

**Time spent this session: 1 hour**
<hr>

### September 17: Finding Parts on Amazon
I knew I needed to make a robot car, with two motors, a microcontroller, and a motor driver. I decided to look for these components on Amazon. 

**Motors:** Because the Electric Vehicle had to be as thin as possible to get the most can bonus (cans closer together = more bonus points), I needed small motors so my chassis isn't too big. I found a type of motor called an N20 motor, which had a very small size. I found a lot of different options on both the Polulu (robotics parts company) website and Amazon. 
> ![image](https://cdn.hackclub.com/019f0782-4191-776b-af20-a2bc81492fb6/9-17-25%20n20%201.JPG) ![image](https://cdn.hackclub.com/019f0782-5f65-7000-be58-2bdc3d4d8765/9-17-25%20n20%202.JPG) ![image](https://cdn.hackclub.com/019f0782-6d59-73a2-9c3f-74a37c4135f6/9-17-25%20polulu.JPG)

**Microcontroller:** As I don't know too much about electronics yet, I wanted to go with a simple microcontroller that is beginner-friendly. I looked at the popular Arduino Uno R3, and its cheaper alternative, the Elegoo Uno R3. 
> ![image](https://cdn.hackclub.com/019f0781-bc1f-7dfc-ad64-66e7c2fa1060/9-17-25%20arduino.JPG) ![image](https://cdn.hackclub.com/019f0781-cfad-7bd2-884e-41ea785da9e2/9-17-25%20elegoo.JPG)

**Motor Driver:** To control the motors using Pulse Width Modulation (PWM), a motor driver is necessary. I looked at the TB6612FNG module, which is an H-Bridge motor driver.
> ![image](https://cdn.hackclub.com/019f0782-cf6c-7433-ac74-32de8f679f7a/9-17-25%20tb6612.JPG)

Still need to decide which motors, microcontrollers, and motor drivers to buy specifically for my use case.

**Time spent this session: 2 hours**
<hr>

### October 8: Buying Basic Electronics
One thing I didn't discuss in the previous journal is what wheels I was gonna use. This is because I was thinking of using CDs as I have in other vehicle projects, albeit those were not electric. My "Scrambler" project I made previously looks similar to the below picture below, with CDs for wheels. 

![image](https://cdn.hackclub.com/019f0782-f0cb-7ce5-9d35-c97fb01b5ea7/10-8-25%20cds.png) \
However, the CDs broke extremely easily, especially after using superglue to attach them to the axle. After remembering this, I decided to **NOT** use CDs for this project going forward.

The plan is to first buy basic parts like an Arduino, motors, etc., then figure out how to make the vehicle curve/follow and angular path and program it. 

**Steering Method:** First, I wanted to try the caliper steering method, and then the differential steering method if I am unable to implement caliper steering. Caliper steering requires more CADding, and differential steering requires more programming. 

**Parts Choices:** Below is an Amazon cart screenshot of different items I debated on purchasing: (Censored PII)
![image](https://cdn.hackclub.com/019f0783-4523-705e-90d3-b646d7c6fcc2/10-8-25%20amazon-cart.png)
- **Motor**: I went back and reviewed my motor choices. N20 Motors can be used for both differential steering and caliper steering. I looked for some of these on Amazon, and I [found one](https://www.amazon.com/dp/B0F8NLB4CD/), but it didn't have any reviews, so I ended up not purchasing it. 
- **Microcontroller**: I chose to buy the [Elegoo Uno R3](https://www.amazon.com/ELEGOO-Starter-Tutorial-Compatible-Official/dp/B01DGD2GAO/)  because of it being cheaper than the Arduino Uno R3 for the same features, and also got a starter kit so that I could have other electronics to experiment with.
- **Motor Driver:** The [TB6612FNG](https://www.amazon.com/gp/product/B08J3S6G2N/) was more efficient than the L298n Motor Driver, but because I didnt have a [soldering iron](https://www.amazon.com/Soldering-Digital-Welding-Portable-Electric/dp/B08R3515SF/), I decided to go with the L298n instead.

I want to use a 3D-printed frame, a breadboard, and tape if necessary to construct my EV. 

Items I bought today:
![image](https://cdn.hackclub.com/019f0783-b50f-7d7b-bf11-df229f03e453/10-8-25%20final-bought.png)

**Time spent this session: 2.5 hours**
<hr>

### October 14: Experimenting with the Basic Kit
I got my Elegoo Starter Kit and started experimenting with it. If I need it, I'll get a Raspberry Pi Pico later. 

The battery pack had 12V and GND wires, but the ends were too big to fit into the breadboard power rails easily. This made it so the LED didn't light up.

![image](https://cdn.hackclub.com/019f0783-ec3d-797d-b11b-6756915bc9a6/10-14-25%20failed-led.png)

I decided to use the power pins from the Elegoo Uno, and using a resistor made the LED light up properly and not burn out.

![image](https://cdn.hackclub.com/019f0784-8121-7b34-a81e-890a03398e22/10-14-25%20led.png)

This is my first successful circuit!

**Time spent this session: 1.5 hours**
<hr>

### October 18: Motor Movement
I got the motor driver and motor, so I could finally start some moving parts. The L298n had screw terminals to attach the motors and other wires to. 

I made an Arduino program to make sure my motors worked. It spins the motor forward, spins it the other way, then stops. I also added interrupts to the encoders so I could track motor position on the serial encoder.

![Motor Setup](https://cdn.hackclub.com/019f0789-1924-7b2f-893e-19ed62f7959e/paste-1782537852265.png)

Demo of Motor moving: https://youtu.be/Mmbqhapk2sQ

I also got a caliper for caliper steering and measurements, but I think its too cheap because it doesn't have two digits of decimal precision, only one, and it also is very bendy.

![Caliper](https://cdn.hackclub.com/019f0789-f862-7e97-b46c-c904b85435e8/paste-1782537909250.png)

**Time spent this session: 4 hours**
<hr>

### October 19: Steering Design Brainstorming
I made some sketches on how I could make the vehicle turn to go through the cans. I wanted to make the front axle be able to rotate horizontally, using either a screw or a hinge.
- **Screw:** The front axle would be able to rotate by being attached a screw, and this rotation would be tracked by a rotation sensor. ![Screw](https://cdn.hackclub.com/019f079a-541a-7a8d-92d2-9f0206a3e32a/paste-1782538981611.png)
- **Hinge:** The front axle would be attached on one side to a piece that would be attached by a hinge to the rest of the chassis, and the caliper on the other side of the front axle could be used to move it forward and back. As one end of the front axle is secured, the axle will be in an angled position. ![Hinge](https://cdn.hackclub.com/019f079a-d312-7bb3-a8ca-a9b7f1afc1fd/paste-1782539014469.png)

I also researched different motor options, such as: 
- [Polulu](https://www.pololu.com/product/5213), which was too expensive at >$30.
- [Amazon N20](https://www.amazon.com/Lheng-Miniature-Geared-Encoder-265RPM/dp/B07RXCPSQR/), which was too low voltage and RPM (6V & 265 RPM, when I needed 12V & 600 RPM).
- [**12V DC Motor**](https://www.amazon.com/Motor-Encoder-Speed-Gearmotor-Robotics/dp/B07GNDG2NC/), which was my final choice as it would be a strong motor with quadrature encoders included. 

In addition, I researched absolute encoders to measure angle rotation of the front axle: [AS5600](https://www.adafruit.com/product/6357) and MT6701, and the MT6701 is better as it works at higher speeds.

At the moment, I don't want to use a pre-made kit and want to find the parts and design everything myself.

**Time spent this session: 3.5 hours**
<hr>

### November 6: Debating Buying a Kit
I've been thinking about making my own design, but it seems very challenging to CAD a working chassis for either differential or caliper steering design. 

I looked at the [Tektite Vehicle Kit](https://tektitebiz.com/product/electric-vehicle/ 
), but finally didn't end up buying it.

**Time spent this session: 0.5 hours**
<hr>

### November 7: Looking at caliper steering design
I looked at a caliper steering implementation that I found on a forum online, and it seemed very complicated for me to CAD and implement. 

![Caliper](https://cdn.hackclub.com/019f07a5-2573-7dd1-8ac8-8eae3406cac5/paste-1782539690245.png)

I couldn't fully understand it even after looking at it for a few minutes and trying to visualize how I could design it. 

**Time spent this session: 0.5 hours**
<hr>

### November 13: Chassis Manufacturing Problem
I thought about how I would actually manufacture my vehicle chassis today. The only 3d printers I have access to are the school's Dremel Digilab printers, which have max build length of like 6 inches. This is probably too small for my caliper frame, and I'd have to design it differently.

**Time spent this session: 0.5 hours**
<hr>

### November 17: Different Microcontroller Options
I re-evaluated different microcontroller options, this time looking at ESP32, RPI Pico 2, and STM32. While I found that they are basically the same, ESP32 also has wifi/bluetooth capability, which could be helpful for programming. 

I also realized I need a better caliper for caliper steering, as the method needs precision in order to function and turn the vehicle accurately. 

In addition, I looked at another caliper steering design, this time looking at the front axle mount. 

![Front Axle Mount](https://cdn.hackclub.com/019f07ad-dd3c-747d-bbeb-f30f6ba66d46/paste-1782540261775.png)

With this, I would angle this mount based on the track length, with a lesser angle for longer track lengths. The vehicle would also start at an angle based on math and arcs. I would also use a scope to aim at the cans or endpoint. 

**Time spent this session: 2 hours**
<hr>

### November 18: Vehicle CAD with all current Materials
I decided to collect all the materials I had and make a CAD of my planned vehicle using Onshape. I also used 3d-printable parts from [TopFinishKits](https://topfinishkits.com/vehicle-electric-vehicle/) to make my CAD. However, this CAD can only go straight, so it needs to be changed in the future. 

![All Materials](https://cdn.hackclub.com/019f07b4-1420-76c8-a902-b9b58a073252/paste-1782540668931.png)![CAD](https://cdn.hackclub.com/019f07b5-9e01-7941-8619-8c3cc07bd823/paste-1782540769084.png)

**Time spent this session: 2 hours**
<hr>

### November 25: Purchasing Acurun Kit
While I had previously not wanted to buy the Acurun kit, after spending time trying to design a caliper steering kit, I realized I do not presently have the skills to achieve this. This is why I decided to buy the [Acurun EV](https://www.youtube.com/@AcuRunKits) kit off Etsy. \
The kit comes with a chassis STL file, two N20 Motors, a castor ball, a 6xAA battery pack, a SS1306 OLED display, a TB6612FNG motor driver with soldered headers, and wires. It does **NOT** come with wheels or the microcontroller. 

![Acurun Kit](https://cdn.hackclub.com/019f07e3-1986-7299-9c91-019902b900c8/paste-1782543750556.png)

**Time spent this session: 2 hours**
<hr>

### November 27: Path Planning
I decided that caliper steering was too complicated, and I wasn't able to modify the previous journal's design to curve. \
The Acurun Kit uses differential steering, and I drew two possible paths for my vehicle in Freeform.

![image](https://cdn.hackclub.com/019f07d1-7f7c-7d80-96b6-9f2806727875/paste-1782542596440.png)

- **Blue:** Start the vehicle pointed diagonally towards the midpoint between the cans. The vehicle goes straight towards the cans, turns, and goes straight to the endpoint. 
- **Red:** Start the vehicle pointed straight towards the endpoint. The vehicle goes straight, then turns diagnoally to the left and continues. When the vehicle intersects with the vertical line going through the midpoint of the two cans, it turns to the right and goes straight through the cans. After, it turns to the right and goes diagonally until it reaches the vertical line formed by the first straight path. It then turns back to the left and continues straight until the endpoint. 

Planning this out now will help me program the differential drive later. 

**Time spent this session: 0.5 hours**
<hr>

### December 15: Kit Delivery
The Acurun EV kit was delivered and I began assembling it. However, I did not have a microcontroller or wheels or chassis, so I could not begin programming or testing. 

![Kit Package](https://cdn.hackclub.com/019f07e5-2b54-792f-9241-4d04ec126eff/Screenshot%202026-06-27%20at%2012.00.49%E2%80%AFAM.png)

**Time spent this session: 1 hour**
<hr>

### December 20: Confirming ESP32 Usage Legality
Because the kit did not come with a microcontroller, I had to obtain my own. As discussed previously, the ESP32 would be a good option due to its wireless capabilities. I confirmed that I can use it according to the rules as long as I do not use the wireless capabilities during competition. 

**Time spent this session: 0.5 hours**
<hr>

### December 21: Getting an ESP32
I got an ESP32 from the Prototype Hackathon. Because my project used an ESP32 DevKit V1 Board, I was allowed to keep it, and I can use it for my vehicle project.

![ESP32 Device](https://cdn.hackclub.com/019f07e7-be5f-7c80-adb5-179940dc5031/IMG_8061.jpg)

**Time spent this session: 1 hour**
<hr>

### January 14, 2026: Finalizing Microcontroller and Manufacturing Wheels
I decided to finalize my usage of the ESP32 Microcontroller. \
This is because if I went with the RPI Pico, I would need a 12v->5v buck convertor to ensure the battery doesn't burn out the RPI Pico (which can only accept 5v), and there is not enough space on my vehicle for that. \
In addition, I am using a 9v (6x1.5vAA) battery pack to make sure I don't burn out any of the hardware. \
I also made the decision to 3D print banebots wheels instead of buying them to save costs. 

Banebots Wheel CAD (1.625 in Diameter, 0.625 in Width):
![Banebots Wheel CAD](https://cdn.hackclub.com/019f07f0-848b-7dc5-b2f4-a3bf1fa35070/paste-1782544630015.png)

**Time spent this session: 1 hour**
<hr>

### January 26: Sent files for print
I asked my Video Game Design/Engineering teacher at my high school to 3D print the frame and wheels on the 3D printer. He printed it on his home Bambu Lab X1C 3D printer. 

![Frame CAD](https://cdn.hackclub.com/019f07f4-14cc-7fc4-880d-1fec289c68ed/paste-1782544863786.png)

(Banebots Wheel CAD in previous journal)

**Time spent this session: 0.5 hours**
<hr>

### January 28: Print Quality and Assembling Vehicle
My teacher gave me the completed 3D prints, and I assembled the vehicle. \
Because he didn't print the wheels with supports, the print quality was messed up and I had to use a box cutter knife to remove some of the stringing. \
I also had to cut away some of the plastic from the inside hole of the wheel, as it was not fitting on the wheel hubs on the motors. \
![Wheel with Plastic Bits](https://cdn.hackclub.com/019f07f7-eb3f-734b-812c-22d9e8eb24a4/paste-1782545114432.png)

I assembled the vehicle, connecting the wires to the different components using this wiring diagram, but modified to use an ESP32 DevKitV1 instead of an Arduino Nano 33 BLE:

Wiring Diagram: ![Wiring Diagram](https://cdn.hackclub.com/019f07f9-34bc-7b80-9cb1-baed53fc2183/paste-1782545199022.png)

Images of Assembled Vehicle: ![Side 1](https://cdn.hackclub.com/019f07f9-a09b-7d65-88ac-0fcdc60ceccc/paste-1782545226917.png) ![Side 2](https://cdn.hackclub.com/019f07f9-d523-7e41-a38c-b09c1fdf9c7b/paste-1782545241001.png)

However, since the ESP32 is pretty big, it kept moving around as it wasn't secured and kept touching the wheels. 

To add grip to the wheels to make it actually move when on the ground, I am planning on using grip tape or rubber bands. 

**Time spent this session: 4 hours**
<hr>

### February 1: Setting Deadlines
I want the vehicle to be ready by 02/21 for the StanfordSO Invitational. This means I need to begin programming and get it competition-ready quickly.

**Time spent this session: 0.5 hours**
<hr>

### February 3: Choosing Path to Program
I want to use the BLUE turning method because it seems simpler to implement, with less turns to make it less complex to program. The RED turning method seemed simpler at first cause of aiming it straight forward but the turns are very hard to implement. 

I also might wanna switch to RPI Pico because the ESP32 is very big, and it's not fitting on the chassis properly.

**Time spent this session: 0.5 hours**
<hr>

### February 4: Programming with PID and Trapezoidal Motion Profile
I began writing code using the Arduino IDE and the help of Claude. 
- Program 1: I wrote a program that uses the N20 motors, encoders, display, and motor driver to make a simple path. It goes forward a set distance, turns 90 degrees, and drives forward again. This uses the quadrature encoder interrupts to count and figure out when to turn. 
- Program 2: To improve the straight-line accuracy and start and ending accuracy, I decided to use a closed-loop PID controller and a trapezoidal motion profile. This allows the vehicle to accelerate and decelerate at the beginning and end of each path, meaning it slips a lot less. When I press the button, it goes straight, turns 90 degrees twice, and ends accurately at an endpoint. 

**Time spent this session: 5 hours**
<hr>

### February 7: Fixing wiring problems
While uploading some new code, the hardware just refused to move. I realized this was for a few reasons:

1. The ground pins of the battery pack, ESP32, motors, and TB6612FNG motor driver were not all connected. Without this connection, the electricity won't flow where it needs to and the motors will not move.
2. The STBY (standby) pin of the TB6612FNG needs to be activated for the h-bridge motor driver to actually function. I pulled it up with 3.3v and it started working again.
3. I realized I wired my ESP32 incorrectly and used the bootup/strapping pins for GPIO. I rewired the ESP32 connecting everything to proper GPIOs and everything started working again. 

**Time spent this session: 3 hours**
<hr>

### February 9: Focusing on Motor Driver 
I investigated the TB6612FNG library and its included examples. I wanted to understand how the TB6612FNG motor driver worked, so I used the different programs to control the motors. 

The script moves each motor forward, backward, braking, and moves them together forward, backward, and braking. It also allows the robot to move in one direction like left/right, which is important for my vehicle to be able to follow the path. 

Because I know how the TB6612FNG works properly, I can start programming my vehicle more easily now. 

**Time spent this session: 2 hours**
<hr>

### February 10: H-Bridge Library problems
I tried using [this](https://github.com/pablopeza/TB6612FNG_ESP32/blob/master/examples/motors/motors.ino) TB6612FNG library for ESP32, but it didn't work. I think its because the pins weren't assigned properly, or the logic didnt work for my version of the ESP32.

Instead of trying to fix the library, I decided to start programming it like any other H-Bridge like l298n, and made a script that directly toggles the raw digital outputs (HIGH/LOW) for the direction pins (AIN1/AIN2 and BIN1/BIN2) and drives the speed using standard Arduino analogWrite() PWM signals.

I added to the script to drive the motors forward and backward and track encoder positions to the serial monitor, so I could ensure the motor driver and encoders were working together properly.

**Time spent this session: 3 hours**
<hr>

### February 11: Space Constraints Problem
Because the ESP32 doesn't fit on breadboard, it makes wiring really annoying. This is why I began to reconsider the Arduino Nano 33 BLE option, as it is really really small, like almost half the width of the ESP32. 

I still decided against using it because it is much more expensive than the ESP32, and I don't have enough time to get it and then program it. 

**Time spent this session: 0.5 hours**
<hr>

### February 12: Rubber Banded Wheels Failure
![Vehicle Image](https://cdn.hackclub.com/019f0813-e01b-71f3-8559-42081e66b35c/paste-1782546946575.png)

The vehicle has rubber bands on the 3D-printed wheels for grip. The ESP32 is being held up by the wires and their rigidity. 

A major problem was when I tried making it drive on the floor, and even when I just programmed it to go straight, the rubber bands caused horrible wobbles that led to it falling over. Even using PID didn't really help, as the wires still got caught. I need to probably switch to proper Banebots wheels and wire it properly.

**Time spent this session: 3 hours**
<hr>

### February 15: GND Pin Confusion
There are two GNDs on the TB6612FNG motor driver. I thought I had to connect both of them to the ESP32. However, there are only two GND pins, and one of them is already being used for a different component.

To fix this, I thought of soldering two wires coming out of the two GND pins on the motor driver together. I realized this was unnecessary, however, as only one GND pin needs to be connected to the ESP32. 

**Time spent this session: 2 hours**
<hr>

### February 16: SparkFun Library and Path Selection
I experimented [TB6612FNG SparkFun Library](https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library) to control the motors. The vehicle moved and went straight, without any implementation of encoders or a PID control loop. 

I modified the BLUE path and considered both options again:
![Paths](https://cdn.hackclub.com/019f081c-159a-71ce-8834-a3f354c81b98/paste-1782547485438.png) \
This time, the BLUE path turns before reaching the cans, and goes straight through it instead of turning at the cans. This is because there is not much space to turn in between the cans, especially when the cans are closer together for more bonus points. 

I decided to wait to program until my Banebots wheels arrive. 

**Time spent this session: 2 hours**
<hr>

### February 18: Wheels Delivery Delay
The wheels are arriving on 2/21, the day of the competition, so I won't have a vehicle ready for the competition :heavysob:.

**Time spent this session: 0.5 hours**
<hr>

### February 22: Wheels Delivery Delay x2
Our school did not permit us to attend the StanfordSO Invitational, so it ended up not mattering that I did not have the wheels on time.

Unfortunately, the wheels got delayed again by two days so I still can't program. 

**Time spent this session: 0.5 hours**
<hr>

### February 24: Wheels Arrived, Programming PID
I got the Banebots wheels and attached them to the motor hubs. It now moves but without encoders and PID.

I made a new program. It has two PID loops, one for each motor to make sure the PWM changes dynamically for each motor's errors. It also has interrupts for the encoders seperately on each motor to get input for the PID loops. 

I had to fix the wiring again with the STBY and VM pins causing problems. I also rewrote the PID to output raw PWM instead of velocity values. 

This spun the wheels properly and I can now program it smoothly.

**Time spent this session: 4 hours**
<hr>

### February 26: Made a Graph for Path Planning
I measured my EV and it came out to a width of 5.25 cm.

I made a graph on Desmos that dynamically updated the can location based on the length of the track.

![Graph](https://cdn.hackclub.com/019f083b-307a-71bc-97af-1495e1fe55b2/paste-1782549523980.png) 

I hope to use this in conjunction with trigonometry and arcs to make path planning easier.

**Time spent this session: 1 hour**
<hr>

### March 2: IMU Consideration
I have decided on the RED path. 

To control turning, I can either use raw encoder output, or I could integrate an IMU with a gyroscope to measure what direction the robot is turning. 

IMU Options are BNO085, BNO055, and MPU6050. \
I looked at all of them, with their costs, and how to implement them, and decided that it would take too long for them to deliver, are too expensive, or would be too difficult to implement.

**Time spent this session: 2 hours**
<hr>

### March 7: ESP32 Burnout 
So I made a mistake today. 

When connecting the power wire from the battery pack to the ESP32, I mistakenly connected it to the 3.3v pin instead of the VIN pin. 

The only reason the ESP32 was able to work with 9v battery line is because of the LDO (Low-Dropout Regulator) that lowered the voltage coming in from the VIN pin. Since I mistakenly connected it to the 3.3v pin, the voltage wasn't reduced and the components on the board were fried. 

I felt extremely demotivated, especially considering the Regional Tournament, the final competition, was in one week on 3/14. 

I still decided to keep pushing, and purchased a pack of 3 ESP32 DevKit V1s from Amazon for like $10. 

I also then reviewed the voltage necessary for my motors. 

I had to make sure that I connected the VCC pin on the motors to the VCC on motor driver, and the motor driver was connected to the 9v. 

I am currently using 6V N20 motors, so it *can* run on 9v but will overheat. The 3.3v from the motor driver is a better power source. 

**Time spent this session: 3 hours**
<hr>

### March 8: More Material Options
I'm beginning to be able to fully understand how to program it now.

![Messy Desk](https://cdn.hackclub.com/019f0a59-5636-7867-95ef-818dee228adc/paste-1782585053751.png)

I miscalculated the length of the track. I mistakenly thought the track was 10-20 meters, and the target time was 7-10 seconds. However, it was the reverse, with track length 7-10 meters, and target time 10-20 seconds. This meant I had to spend a lot of time reprogramming and setting new speeds for the motors. 

I then made the vehicle too fast, and it crashed into the wall repeatedly. 

I still haven't figured out how to turn the vehicle properly yet. 

The ESP32 in the EV gets warm, probably because 9V is a high voltage for just a LDO. The [Tektite RotEv Controller](https://tektitebiz.com/product/rotev-controller/) could solve this using a buck convertor, but would take too long to ship.   

To solve the warmth of ESP32, I thought about switching from Alkaline batteries to NiMH batteries, as 6xAlkaline = 9v while 6xNiMH = 7.2v. NiMH batteries are also rechargeable. I ended up not buying them because of time and money constraints. 

I also ran out of Claude prompts so I had to continue to manually program. 

Also, I looked at some example programs, that used a RAMSETE controller, but it needed multiple cores so it wasn't possible with just interrupts on ESP32.

**Time spent this session: 3.5 hours**
<hr>

### March 9: PID & Trapezoidal Motion Profile Implementation
My EV is beginning to work properly now. I implemented a PID loop and trapezoidal motion profile correction.

I used the example code below to understand how to implement a basic PI controller into my code. 

![Example PI Code](https://cdn.hackclub.com/019f0a6a-1e3d-7624-8093-fb81e13a96ea/paste-1782586153698.png)

I also analyzed the below diagram. It uses encoder output to find the measured speed and position of the motor, then compares it to the calculated speed and position. The error gets inputted into a PID controller, Proportional Integral Derivative, and then outputs a PWM as a percentage of motor voltage. 

![image](https://cdn.hackclub.com/019f0a75-e58e-76da-bd48-cd53eb1a6c91/paste-1782586925688.png)

Now I just have to test turns until the Vehicle follows the correct path, and then make some equations to determine how long to delay before starting movement for each distance to hit the target time.

I looked into a method of path following called Pure Pursuit, but it wouldn't work since I do not have an IMU. 

It took a while for me to implement the trapezoidal motion into PID and curves, but I was able to get it to work. 

I also made the last 50 cm of the path slower than the rest to ensure it doesn't skid past the end point. 

I used the Serial Plotter in the Arduino IDE to analyze the target RPM vs Measured RPM. 

![Serial Plotter](https://cdn.hackclub.com/019f0a82-b294-70f6-abf3-6b8c8f5ee679/paste-1782587764162.png)

To fix the oscillation, I needed to add a kV or Feed Forward value, which is a constant multiplied by velocity. I can also increase the I value in PID to smooth out the oscillations. 

**Time spent this session: 5 hours**
<hr>

### March 10: Motor Stalling Issues
When testing my vehicle, the motors started making crackling noises when I put it on the ground. They spun again when I lifted it.

After checking online, I realized this is because the motors were stalling from not having enough power. This is because the batteries were running out of power very quickly from the high power draw the motors had.

I had to replace batteries frequently (every 3-5 runs) to ensure accuracy and prevent stalling.

**Time spent this session: 2 hours**
<hr>

### March 11: Trapezoidal Motion Profiles
I looked at some more graphs and example code to understand how to implement trapezoidal motion profiles to reduce skid for my vehicle at the end of each segment. 

The graph below shows how I can program the robot to accelerate and decelerate at the beginning and end. This is to ensure that the vehicle travels precisely. Without the acceleration and deceleration periods, the motor would not accurately shift speeds and the vehicle wouldn't end up in the correct place.

![Trapezoidal Motion Graph](https://cdn.hackclub.com/019f0aad-7963-7f62-9744-35103f325c78/paste-1782590568307.png)

The below code is an example implementation of the above graph. 

![Graph Implementation Code](https://cdn.hackclub.com/019f0ab0-1d39-71a1-a296-5d26b7df12a3/paste-1782590741128.png)

After implementing code similar to the above to have a trapezoidal shape graph in my code, I got the below results in the Serial Plotter, which were pretty good for my vehicle use case:

![Serial Plotter](https://cdn.hackclub.com/019f0ab3-4528-7a01-9387-d9021fae97a8/paste-1782590947486.png)

**Time spent this session: 3 hours**
<hr>

### March 12: Tweaking the Program
With the March 14 deadline coming up, I realized I wouldn't be able to get it perfect without another week to work on it. So I just hoped to make it good enough to use in competition. 

I got it to go in circles like a race car, which is not very helpful, but at least its moving in one direction. 

My straight line segments of the path were still inconsistent, so I had to continue to tune PID and trapezoidal motion.

I also checked the rules and rules clarifications to ensure that I can tape my battery pack to the EV after impounding it. This is because batteries need to be impounded separately, and I need to be able to attach the batteries again after impounding it. Also, the only way to attach the battery pack to my ev is by taping it.

**Time spent this session: 4 hours**
<hr>

### March 13: The Final Work Day
As the competition is tomorrow, today is the last day to work on the EV. I ended up staying up until 3AM to work on the EV, with competition at 7AM :sob:. I wish I had someone to work with me this late. 

List of Problems I Worked Through Today/Tonight:
- **Pausing between each segment**: Due to implementing trapezoidal motion, the vehicle stopped after each straight/turn section. This added a lot of time meaning I wasn't able to reach the target time. I had to remove the trapezoidal motion in between to make the delta calculations for acceleration and deceleration not mess up. This allowed me to keep most of the code but just remove some parts.
- **Battery problems**: The 6xAA 1.5V Alkaline Duracell batteries ran out of power very frequently with the power draw from the motors. When the voltage dropped, the PID immediately began to fail because it was dependent on constant, full voltage from the batteries. It couldn't reach the RPM necessary and the distances werent consistent or fast enough. I had to buy batteries from Target at like 10pm and it cost another $20. I should have used NiMH rechargeables earlier, but oh well. 
- **Simplifying Path**: Because of the inconsistencies with PID, I decided to make it easier by sacrificing more points from my can bonus. I decided to go with a can width of 25 cm instead of a smaller width of 10 cm. This would save me a lot of headache and make it less risky during competition.
- **Disregarding Time Bonus**: While you get more points for being closer to the target time which is between 7-10 cm, I realized that my vehicle is too slow for this, going around 14-20 seconds instead. This is okay though, as the time bonus score is negligible compared to the distance and can bonus scores. 

**Final Run**: I ended up getting 2 cm away from end point, 14 seconds time, with a 7 cm distance and 50 cm can bonus. I think this is what I'm going to run tomorrow for competition day. 

**Time spent this session: 8 hours**
<hr>

### March 14: Competition Day
The robot went fairly well. I got 4th place overall.

Target Time: 15s \
Target Distance: 9m \
Distance Score: 84cm away from end point \
Time Score: 17.88s \
Can Bonus: None (went to the left of both cans) 


Demo @ Home: https://youtube.com/shorts/tnM1iEZ0sQo \
**Demo @ Competition**: https://youtu.be/8lS0Rzt4JzQ

**Time spent this session: 1 hour**
<hr>

### June 27: README
Today, I CADded the robot in Onshape to make it presentable for the README. I imported a lot of parts from Onshape. I recorded it using Lookout.

![Angle view](https://cdn.hackclub.com/019f0c26-f2bb-7ea4-8bea-5010bff3a317/Screenshot%202026-06-27%20at%207.53.34%E2%80%AFPM.png)
![Side view](https://cdn.hackclub.com/019f0c27-2d90-71c2-aca3-e7d0e5830cd7/Screenshot%202026-06-27%20at%207.53.25%E2%80%AFPM.png)

I also made a wiring diagram using Cirkit Designer. \
https://app.cirkitdesigner.com/project/edc74d5a-a196-4ad5-98cb-bc518ee554fb
![Circuit](https://cdn.hackclub.com/019f0c54-d9e9-736f-880e-26ed64cc8687/circuit_image.png)

And I wrote the README.md.

**Time spent this session: 4 hours**
<hr>
