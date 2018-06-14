# RC-Rover controlled by gestures motions & Joystick  



RC Rover is a Robotics project that aims to improve rover control through the use of radio frequency

and the interaction of rover movement with hand movement using the inertial unit (MPU6050),

but also the control of this Rover with a Joyestik. All this is done remotely using the radio frequency

Nrf24l01 (2.4Ghz) . This project is realized using open source development boards (Arduino), one for data

transmitter (main command) whitch contains the Joyestik and the inertial unit and one for the receiver (control of the engines),

for the transmission i used (Arduino Pro Mini Board )


for the receiver i used (Arduino Uno board )

Parts and Tools Required : 

Parts:

1. 4WD Robot Chassis kit

2. Arduino Uno or nano (for receiver)

3. Arduino Pro Mini for trasmitter

4. 2 * LM298 H bridge Module

5. 12v power supply for Motors

6. 2 * module RF Nrf24l01 (Transmitter and receiver)

7. MPU6050 (accelerometer & gyroscope)

8. FTDI chip or (cp2102) for uploading code in Arduino Pro mini 
9. 2* Breadboard

10. Jumper wires (M-F, M-M and F-F)

11. Joyestick Module with switch


What's is Rover:

Rover is an electromechanical device which is capable of reacting in some way to its environment, and take autonomous decisions or actions in order to achieve a specific task.

A robot is consists of following components

1. Structure / Chassis

2. Actuator / Motor

3. Controller

4. Inputs / Sensors

5. Power Supply



i used Motor library so, you have to download it in : https://github.com/salimkhazem/MotorLibrary

after that, you  must add the libraries to the Arduino libraries folder.

To do this : you must copy the folder "Motor" paste them in the arduino libraries folder.

-Download the RF24.h library and move it to the Arduino libraries folder.

https://github.com/maniacbug/RF24


Contribution:

If you want contribute:

Fork the project
Add your branch
add your commits
Finally push your pull request



for more information or details about the project visit : https://www.instructables.com/id/RC-Rover-Controlled-by-Gestures-Motions-Joyestick/ 

or in Hackster:  https://www.hackster.io/salimkhazem97/rc-rover-controlled-by-gest-7bc2e9 
