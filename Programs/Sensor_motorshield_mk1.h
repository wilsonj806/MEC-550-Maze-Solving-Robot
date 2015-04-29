/*
 ********************************
   MEC 550 Maze Solving Robot
   Hallway Navigation Program
    Version 1 April 9, 2015
 *******************************
 
 ********************************
        Change History
 ********************************
Version 1 4/9/15
- Created base version of the program
- NOTE: THIS PROGRAM USES ULTRASONICS SENSORS
  TO RUN. FOR THE FINAL PROGRAM, THIS PORTION
  SHOULD BE CHANGED TO ACCOUNT FOR INFRARED SENSORS
  RATHER THAN ULTRASONIC SENSORS
 *********************************
        End Change History
 *********************************

This program is made in order to have the robot navigate a hallway
without crashing into walls. That would be bad and should be avoided at
all costs.

*/
#include "MotorDriver.h"

int echoPin = 4;
int trigPin = 12;
int echoPin2 = 2;
int trigPin2 = 13;
/* echoPin is the left facing sensor
   echoPin2 is the front facing sensor
*/
int i =1;
unsigned long Ao = 100;
unsigned long Bo = 100;
word duration, dnom,dl, dur2, dnom2,dx;
int AA, BB, Ai=0, Bi=0, delD,delL;
/* dl is in mm  
    tcal is calibrated turn time, awesome sauce
    dnom is nominal distance in mm
    delD is the difference between dnom and dl AND MUST HAVE A SIGN
    AA = motor power A
    BB = motor power B
    Ai = power to A modifier=
    Bi = power to B modifier
    Ao and Bo are standard powers
    Do not need to have motor pin variable due to the whole motor shield library
*/
void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPin2, OUTPUT);
    motordriver.init();
}
void loop() {
 while (i<33){
// For left facing sensor
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
// Output a low frequency thing to allow for a clean higher freqency reading
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
// High frequency waveform that will be read by the sensor
 duration = pulseIn(echoPin, HIGH);
// pulseIn reads the high frequency pulse from echoPin as a time
 dl = duration/5.8;
 dnom = 26;
 delD = dnom-dl;
 
 // For Front Facing Sensor
 digitalWrite(trigPin2, LOW);
 delayMicroseconds(2);
 // Output a low frequency thing to allow for a clean higher freqency reading
 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin2, LOW);
 dur2 = pulseIn(echoPin2, HIGH);
 dx = dur2/5.8;
 dnom2 = 30;
 delL = dnom2-dx;
 // This is hte problem spot
 // pulseIn reads the high frequency pu
// Motor driving portion
 AA=Ao+Ai;
 BB=Bo-Bi;
 motordriver.setSpeed(AA, MOTORA);
 motordriver.setSpeed(BB,MOTORB);
// Motor A is the right motor, Motor B is the left motor
  motordriver.goForward();
   delay(3);
 if(delD < 3 && delD >0){
  Ai=delD*2;
  Bi=delD*2;
 }
// avoding the wall, but not that close
   else if(delD < 6 && delD>0) {
  Ai=delD*4;
  Bi=delD*4;
   }
// avoiding the wall, getting too close


// Stop the robot
   else{
     Ai=0;
     Bi=0;
    continue;
// shit goes straight otherwise
   }

}
}
