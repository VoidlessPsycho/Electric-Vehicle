# Voidless's Electric Vehicle

This project is an Electric Vehicle for the Science Olympiad Electric Vehicle event for the 2026-27 season. It uses N20 Motors, TB6612FNG Motor Driver, and ESP32 for movement.

**Demo Video:** https://youtu.be/8lS0Rzt4JzQ

![Angle View Front](https://cdn.hackclub.com/019f0c2b-0987-74f2-90e0-b2681d8d7356/IMG_8068.jpg)
![Angle View Back](https://cdn.hackclub.com/019f0c2b-2e37-7212-a7a3-944db897079a/IMG_8069.jpg)

[Journal](JOURNAL.md)


## How to Use
1. Turn on power by pressing button from battery pack.
2. Upload code from computer using USB-C and Arduino IDE.
3. Align toothpick and vehicle with start point on track, facing straight forward.
4. Use a pencil to press button in center of vehicle.


## How it Works
1. Pins are assigned to variables.
2. There is a configurable segments object to determine how far to go for each segment of the path. 
3. When the button is pressed, the motion part of the script activates. 
4. The vehicle uses encoder feedback and compares it to the calculated position of each motor to determine which segment the vehicle currently needs to be on, and uses PID loops and if statements to control the vehicle speed and direction.
5. The vehicle stops once it is detected that the vehicle has passed through all the segments. 


## Tech Stack
- Arduino IDE
- C++ (Programming)
- Onshape (CAD)
- Freeform/Excalidraw/Notebook (Brainstorming)
- Desmos Graphing Calculator (Path Planning)
- VS Code (Repository Management)
- Markdown (Journaling/Documentation)

AI Declaration: AI was used in programming the firmware for this device. 

## Images
CAD: \
![Front](https://cdn.hackclub.com/019f0c33-b7e1-7785-bcde-1f1280ff59af/Screenshot%202026-06-27%20at%207.53.34%E2%80%AFPM.png)
![Side](https://cdn.hackclub.com/019f0c33-d6fc-7178-a627-3f2718fa5d2e/Screenshot%202026-06-27%20at%207.53.25%E2%80%AFPM.png)

[Wiring](https://app.cirkitdesigner.com/project/edc74d5a-a196-4ad5-98cb-bc518ee554fb): \
![Circuit](https://cdn.hackclub.com/019f0c55-5452-79d7-9357-30093a92f1fc/circuit_image.png)

Bill of Materials:
- 1 x Push Button
- 1 x 6xAA Battery Holder
- 6 x AA Batteries
- 1 x Ball Castor
- 2 x Banebots T40 1.625x5/8 in Wheels + Hubs
- 2 x 12V 1:30 Gearbox Polulu N20 Motors with Encoders
- 1 x ESP32 DevKit V1
- 1 x TB6612FNG Motor Driver
- 1 x 3D Printed Frame
- 1 x 3D Printed Motor Holder
- Dupont Wires (Female-Female)


## Motivation
I selected this event for Science Olympiad as I was interested in electronics. This event requires programming a microcontroller with C++ and learning motor control structures, like using PID control loops, trapezoidal motion profiles, and H-Bridge motor drivers. This project is meant to be a competitive device for the Electric Vehicle event, and I won 4th place with it at my Regional Tournament. 