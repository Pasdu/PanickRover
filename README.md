# PanickRover

The purpose of this project is to create a scheme to control a treaded 'rover' robot that is to evolve over time from a manually controlled bot to an autonomous robot that is able to learn about its environment and interact with certain elements within that environment.

Current Task: Reach version 1.0 (Marionette)

Current version: 0.7 (Completely arbitrary)
'RobotControl100.ino' 

## Available Functions:

**void SetMotorDirection(int motor = 2, bool reverse = 0)**

Sets the direction of a given motor


**void SetSpeed( int motor = 2, int value = 0)**

SetSpeed must be given an integer to tell it which motor to set the speed for, and a value from 0 to 100 (expressed as a percentage of maximum speed). It scales the value into a number from 0-255 (the range of the analog output).


**'void MoveForward()' and 'void MoveReverse()**

MoveForward is designed to move the robot straight forward using the current reference speed, any turn ratio set or left/right motor speed settings will not affect this function


**'void JogForward()' and 'JogReverse()'**

This function takes into account the individual speed settings for the left and right motors and applies forward or reverse power at those given speeds.


**'void Stop()'**

Turns off any output for the left and right motors


**'void SetRatio(bool left = true, int turnFactor = 2)'**

Establishes a turn ratio in the left and right speed variables. It takes the current speed of the treads, divides that value by a given scaler and sets the inside tread to that value based on the desired direction of turning.
This function must be given the following values:
bool "left": If it equals true the robot will make a left turn
int turnFactor The value that the speed will be divided by, higher values make for sharper turns.


