/************************************************************
* Robot control version 1.0                                 *
* Code by Michael Walsh                                     *
* using the DFRobotShop Roverr V2.0 Base                    *
* Code Started on : Saturday, April 16th, 2016              *
* I know nothing of the legal details regarding this code   *
************************************************************/

//Load Dependant Libraries
#include <IRremote.h>

//Define some constants that the robot will use
const int topSpeed = 100;
const int midSpeed = 60;
const int lowSpeed = 30;

//Variables used by the robot to keep track of shit
int leftSpeed = 0;
int rightSpeed = 0;
int speedReference = 100;

//Establish Standard Pins for Motor Control
int leftSpeedPin = 6;   //Left Motor Speed Control
int rightSpeedPin = 5;   //Right Motor Speed Control
int leftMotorPin = 8;   //Left Motor Direciton Control
int rightMotorPin = 7;   //Right Motor Direction Control

//Establish Standard Pins for Sensor input
int IRpin = 11;    // Establishes the Pin number for Infrared Input

//Variables that manage the infrared receiver code functionality.
unsigned lastCode = 0;
int lastTime = 0;

//Initialize Infrared Receiver
IRrecv irrecv(IRpin);
decode_results results;

//Function Prototype for SetRatio because it doesn't like me
void SetRatio(bool left, int turnFactor);

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  
}

void loop() {

    // This line checks if anything has been received and makes the code available to read.
    if(irrecv.decode(&results)){
      //Is this code a new one or a repeat?
      int thisCode = results.value;
      if(thisCode != lastCode){
        //Serial.println(results.value);
        lastCode = thisCode;
        //Now we can interpret the code and carry out the behavior.
        switch(results.value){
            //Forward Motor Case
            case 2774159535:
              MoveForward();
              Serial.println("ForwardCommandSent");
              break;
            //Reverse Motor Case
            case 2774192175:
              MoveReverse();
              Serial.println("ReverseCommandSent");
              break;
            //Turn Left Signal (Pre-set turn)
            case 2774172030:
              SetRatio(true, 2);
              JogForward();
              Serial.println("Turn Left Command Sent");
              break;
            //Turn Right Signal (Pre-set turn)
            case 2774139390:
              SetRatio(false, 2);
              JogForward();
              Serial.println("Turn Right Command Sent");
              break;
            //Steering Left Command
            case 635103765:
              Serial.println("Steer Left Command");
              break;
            //Steering Right Command
            case 635071125:
              Serial.println("Steer Right Command");
              break;
            //Jog Forward Command
            case 2774141175:
              JogForward();
              Serial.println("Jog Forward Command");
              break;
            //Jog Reverse Command
            case 2774168205:
              JogReverse();
              Serial.println("Jog Backward Command");
              break;
            //Power Signal Command
            case 2774153415:
              Serial.println("Power Command");
              break;                                    
        }
      
      
      }
      irrecv.resume(); //Receive the next value
      lastTime = millis();
    }else{
      //If the timeout period has expired (95 milliseconds)
      int codeTime = millis();
      if ( (codeTime - lastTime) >= 95 && lastTime != 0){
        //Issue a stop
        Serial.println("---DBG--");
        Serial.println(codeTime - lastTime);
        Serial.println(lastTime);
        Stop();
        lastTime = 0;
        lastCode = 0;
      }
    }
  }

//SetMotorDirection is used to set the direction of the motors
/* The motor param determines which motor we set
 *  0 is the left motor
 *  1 is the right motor
 *  2 is both motors
 * The reverse parameter is a boolean value
 * false means that the motor will spin forwards (relative to the bot)
 * true means that the motor will spin in referse (relative to the box)
 */
void SetMotorDirection(int motor = 2, bool reverse = 0){
  switch(motor){
     case 0:
      digitalWrite(leftMotorPin, reverse);
      break;
     case 1:
      digitalWrite(rightMotorPin, reverse);
      break;
     case 2:
      digitalWrite(rightMotorPin, reverse);
      digitalWrite(leftMotorPin, reverse);
     break;
  }
// Testing Code
//This code is providing debugging information to me in the most hackish and unclassy way I can think of
Serial.println(digitalRead(leftMotorPin));
Serial.println(digitalRead(rightMotorPin));
Serial.println(analogRead(leftSpeedPin));
Serial.println(analogRead(rightSpeedPin));
  return;
}

//SetSpeed is used to set the velocity of a given motor, or both
/* The motor parameter is an integer used to define which motor is to be controlled
 * 0 for left motor
 * 1 for the right motor
 * 2 for both
 * The value parameter is a 0-100 value that scales to the minimum and maximum outputs to
 * the motor (0-255), setting this to 0 will cause the motor to not turn and 100 to turn at full speed.
 */
void SetSpeed( int motor = 2, int value = 0) {
  //Turns the 0-100% value given for speed into a 0 to 255 scaled value.
  int scaledSpeed = map(value, 0,100,0,255);

  //Check which motor is the one being changed
  switch(motor){
    //For each case change the current speed and set the output pin to the appropriate value.
    case 0:
      analogWrite(leftSpeedPin, scaledSpeed);
      leftSpeed = scaledSpeed;
      break;
    case 1:
      analogWrite(rightSpeedPin, scaledSpeed);
      rightSpeed = scaledSpeed;
      break;
    case 2:
      analogWrite(rightSpeedPin, scaledSpeed);
      analogWrite(leftSpeedPin, scaledSpeed);
      leftSpeed = scaledSpeed;
      rightSpeed = scaledSpeed;
      break;
  }
// Testing Code
//This code is providing debugging information to me in the most hackish and unclassy way I can think of
Serial.println(digitalRead(leftMotorPin));
Serial.println(digitalRead(rightMotorPin));
Serial.println(analogRead(leftSpeedPin));
Serial.println(analogRead(rightSpeedPin));
}

//This is where the functions that govern the responses generated by the IR Remote

// Forward / Reverse Button functions
/*  This function simply enables or disables both motors in the forward direction
 *  It is designed to set the direction to forward and the speed based on a reference
 *  speed that is specified when the robot is told to change it's 'mode'
 */
void MoveForward(){
    SetMotorDirection(2,false);
    SetSpeed(2, speedReference);
// Testing Code
//This code is providing debugging information to me in the most hackish and unclassy way I can think of
Serial.println(digitalRead(leftMotorPin));
Serial.println(digitalRead(rightMotorPin));
Serial.println(analogRead(leftSpeedPin));
Serial.println(analogRead(rightSpeedPin));
}

void MoveReverse(){
    SetMotorDirection(2,true);
    SetSpeed(2, speedReference);
// Testing Code
//This code is providing debugging information to me in the most hackish and unclassy way I can think of
Serial.println(digitalRead(leftMotorPin));
Serial.println(digitalRead(rightMotorPin));
Serial.println(analogRead(leftSpeedPin));
Serial.println(analogRead(rightSpeedPin));
}

// JogForward and JogReverse
/*  These functions are designed to cause the robot to move but maintain any established
 *   differentials in steering, MoveForward and MoveReverse are designed to use the given 
 *   speed reference and make the robot move striaght forward or reverse, these functions
 *   will take any given turn ratio and use those to propel the bot.
 */
void JogForward(){
  SetMotorDirection(2, false);
  SetSpeed(0, leftSpeed);
  SetSpeed(1, rightSpeed);
}

void JogReverse(){
  SetMotorDirection(2, true);
  SetSpeed(0, leftSpeed);
  SetSpeed(1, rightSpeed);
}

// Stop Function
/*  This function is likely to be sent after a forward command, like an on release
 *  trigger so that the robot actually stops when the user lets go of a motion button
 *  While it is easy to use setSpeed 0 to achieve the same thing, this will ensure that
 *  the robot stops completely quickly with a single command. This function is designed
 *  to bypass the SetSpeed command and kill the speeds. It has no effect on the left and
 *  right speed values.
 */
void Stop(){
  analogWrite(rightSpeedPin, 0);
  analogWrite(leftSpeedPin, 0);
}

// SetRatio Function
/* This function, given a direction and a turn factor. Will use the velocity of the outside
 *  tread to set the inside tread to a lower value and allow the robot to turn. The higher the
 *  turn factor, the sharper the turn will be. This function will cause the robot to turn
 */

void SetRatio(bool left, int turnFactor){
  int newSpeed;
  if ( left == true ){
    newSpeed = speedReference / turnFactor;
    rightSpeed = speedReference;
    leftSpeed = newSpeed;
  }else if( left == false ){
    newSpeed = speedReference / turnFactor;
    leftSpeed = speedReference;
    rightSpeed = newSpeed;
  }
}
