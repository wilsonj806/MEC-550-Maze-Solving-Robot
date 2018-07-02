 /*
 ****************************
  MEC 550 Maze Solving Robot
  Maze Solving Left Wall Nav
   Version 2 May 4, 2015
 ****************************

********************
   Change History
********************
Version 1 - 5/4/15
- Created base version
Version 2 - 5/4/15
- Still tuning large portions
- Robot does not navigate corners as well as straightaways well
- Retuned kpwall so that kpwall = .5
********************
End Change History
********************

Programs that this program borrows:
- color_sensor_streamlined.ino
- Wall_navigation_Mark2.ino
- Adafruit_motor_test.ino (This is on your desktop)
- IR_sensor_distance_read.ino
*/
// Includes prequisite libraries
#include <Adafruit_MotorShield.h>
#include<Wire.h>

#define infrared1 0
#define infrared2 2
#define echoPin 10
#define trigPin 11

// Color sensor pins
#define S0 5
#define S1 6
#define S2 7
#define S3 8
#define servoPin 3
char outputPin = 12;
#define LED 13
// Math variables
int raw1,raw2, front, right, left,sidediff,wallnaverr, state, kpwall, leftspeed, rightspeed, sidediffnom;
long turnrighttime = 450;
long turnlefttime = 450;
long oneeightytime = 960;
word duration;
float rad,graan;

// Variable for confirming that the robot ran the ball grab routine
boolean ballgrab,turnstatus;
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *motorRight= AFMS.getMotor(1);
Adafruit_DCMotor *motorLeft = AFMS.getMotor(2);


/* States are:
 state 0 = color read/ bearing reset
state 1 = check distance
state 2 = decide what to do
state 3 = right turn
state 4 = left turn
state 5 = stragithaway
state 6 = 180° turn
state 7 = T junction
state 8 = dead end
state 9 = ball grabbing
state 10 = terminal
*/

/* Turn times:
Left Turn: 250 ms
Right Turn: 237 ms
180° Turn: 480 ms
*/

void setup(){
pinMode(echoPin,INPUT);
pinMode(trigPin, OUTPUT);
pinsetup();

AFMS.begin();
state = 11;
//ballstate=1;
sidediffnom = 0;
kpwall=.5;
// start declaring where the robot starts
Serial.begin(9600);
}

void loop(){
switch(state){
case 1:
// Read proximity sensor distances
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 // Output a low frequency thing to allow for a clean higher freqency reading
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 // High frequency waveform that will be read by the sensor
 duration = pulseIn(echoPin, HIGH);
 // pulseIn reads the high frequency pulse from echoPin as a time
 front = duration/5.8;
 
 raw1 = analogRead(infrared1);
 raw2 = analogRead(infrared2);
 right = distanceReadr(raw1);
 left = distanceReadl(raw2);
 state = 2;
break;

case 2:
// Figure out options (transitional state)

if (turnstatus==true){
motorRight-> setSpeed(30);
motorLeft-> setSpeed(30);
motorLeft-> run(FORWARD);
motorRight-> run(FORWARD);
delay(400);
motorLeft->setSpeed(0);
motorRight->setSpeed(0);
state = 6;
turnstatus = false;
}
if (left>120){
state = 5;
}
else if (right>120){
state = 4;
}
else if (((left>120)&&(right>120))||((left>120)&&(front>120))||((right>120)&&(front>120))){
state = 3;
}
else if (front<43){
state = 8;
}
else{
  state = 6;
}
break;

case 3:
// T- junction
if  ((left>120)&&(right>120)){
state = 5;
}
else if ((left>120)&&(front>120)){
state = 5;
}
else if ((right>120)&&(front>120)){
state = 6;
}
break;


case 4:
// Right turn
motorRight-> setSpeed(30);
motorLeft-> setSpeed(30);
motorLeft-> run(FORWARD);
motorRight-> run(BACKWARD);
delay(turnrighttime);
motorLeft-> run(RELEASE);
motorRight-> run(RELEASE);
motorLeft->setSpeed(0);
motorRight->setSpeed(0);
state = 11;
turnstatus = true;
break;


case 5:
// Left turn
motorRight-> setSpeed(30);
motorLeft-> setSpeed(30);
motorRight-> run(FORWARD);
motorLeft-> run(BACKWARD);
delay(turnlefttime);
motorLeft-> run(RELEASE);
motorRight-> run(RELEASE);
motorLeft->setSpeed(0);
motorRight->setSpeed(0);
state = 11;
turnstatus = true;
break;


case 6:
// Straightaway (wall navigation)

digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 // Output a low frequency thing to allow for a clean higher freqency reading
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 // High frequency waveform that will be read by the sensor
 duration = pulseIn(echoPin, HIGH);
 // pulseIn reads the high frequency pulse from echoPin as a time
 front = duration/5.8;
 
 raw1 = analogRead(infrared1);
 raw2 = analogRead(infrared2);
 right = distanceReadr(raw1);
 left = distanceReadl(raw2);
if ((right>120) || (left>120) || (front<50)){
motorRight-> run(RELEASE);
motorLeft-> run(RELEASE);
state =11;
break;
}
// do a motor running thing
sidediff = left - right;
wallnaverr= sidediff-sidediffnom;

if (wallnaverr>10){
  wallnaverr=6;
}
else if(wallnaverr<-9){
  wallnaverr=-5;
}
// this is a P controller
leftspeed=kpwall*wallnaverr+20;
rightspeed=20+kpwall*wallnaverr;

motorRight-> setSpeed(rightspeed);
motorLeft-> setSpeed(leftspeed);

motorRight-> run(FORWARD);
motorLeft-> run(FORWARD);

state =6;
break;


case 7:
// 180° turn
motorRight-> setSpeed(40);
motorLeft-> setSpeed(40);
motorLeft-> run(FORWARD);
motorRight-> run(FORWARD);
delay(oneeightytime);
motorLeft->setSpeed(0);
motorRight->setSpeed(0);
state = 11;
break;


/*case 8:
// Dead end
if (rad<40){
state = 9;
}
else if ((rad>60)&&(ballgrab == true)){
state =10;
}
else{
state=7;
}



// check floor tile color
break;
*/
case 9:
// Ball grabbing
/*switch(ballstate){
case 1:
 write(180);
delay(30);
ballstate = 2;
break;
case 2:
 write(0);
delay(30);
ballstate=3;
break;
case 3:
motorRight-> setSpeed(40);
motorLeft-> setSpeed(40);
motorLeft-> run(FORWARD);
motorRight-> run(BACKWARD);
delay(turnrighttime);
motorLeft-> run(RELEASE);
motorRight-> run(RELEASE);
motorLeft->setSpeed(0);
motorRight->setSpeed(0);
ballstate = 4;
break;
case 4:
 write(180);
delay(30);
ballstate = 5;
break;
case 5:
 write(0);
delay(30);
ballstate=6;
break;
case 6:
motorRight-> setSpeed(40);
motorLeft-> setSpeed(40);
motorRight-> run(FORWARD);
motorLeft-> run(BACKWARD);
delay(turnlefttime);
motorLeft-> run(RELEASE);
motorRight-> run(RELEASE);
motorLeft->setSpeed(0);
motorRight->setSpeed(0);
ballstate = 10;
break;
}
ballgrab = true;

*/state = 7;
break;

case 10:
// Terminal state
motorRight-> setSpeed(0);
motorLeft-> setSpeed(0);
state =10;
break;

case 11:
// Color read
//rad = detectColor(outputPin);
graan = detectColor(outputPin);
state = 1;
break;




}

}

// IR sensor calibration curve 
int distanceReadr(int raw1){
float val = 0.0049 * raw1;
int distance =  39.042*pow(val,6)-437.12*pow(val,5)
+1957.3*pow(val,4)-4473*pow(val,3)+5527*pow(val,2)-3620.9*val+1137.9;
return distance;
}

int distanceReadl(int raw2){
float val = 0.0049 * raw2;
int distance =  39.042*pow(val,6)-437.12*pow(val,5)
+1957.3*pow(val,4)-4473*pow(val,3)+5527*pow(val,2)-3620.9*val+1137.9;
return distance;
}

// Color sensor read
int detectColor(char outputPin){
  int red = colorRead(outputPin, 1, 1); // detect % red
  int green = colorRead(outputPin, 2, 1); // detect % green
  return red;
  return green;
}
int colorRead(char outputPin, int color, boolean LEDstate){ // declare color read function as a float
  outputMode(1);
  if(color == 1){
    digitalWrite(S3, LOW);
    digitalWrite(S2, LOW);
  }
  else if(color == 2){
  digitalWrite(S3, HIGH);
  digitalWrite(S2, HIGH);
  }
  float pulseTime; // declare a time for pulse arrival at the "emitter"
  // turn LED on or off
  if(LEDstate == 0){
    digitalWrite(LED, LOW);
  }
 if(LEDstate == 1){
   digitalWrite(LED, HIGH);
 }
 delay(100); // wait for LED to turn on
 
 pulseTime = pulseIn(outputPin, LOW, 80000); // read low voltage pulse from output pin, timeout at 80000
 if(pulseTime <.1){
   pulseTime = 80000;
 }
 outputMode(0);
 return pulseTime; // return the pulse time to the function that calls on colorRead()
}


// Set up the output pin frequency sensitivity
void outputMode(char mode){
  if(mode == 0){
    digitalWrite(LED, LOW);
    digitalWrite(S0, LOW);
    digitalWrite(S1, LOW);
  }
  else if (mode == 1){
    digitalWrite(S0, HIGH);
    digitalWrite(S1, HIGH);
  }
  return;
}
    
// Setting the pin modes
void pinsetup(){
  /* initialize pins/ set all pins but the outputPin as OUTPUT
  S2, S3 is for color selection
  S0, S1 is for communication frequency selection
  */
  pinMode(LED, OUTPUT); 
  pinMode(S2, OUTPUT); 
  pinMode(S3, OUTPUT);
  pinMode(outputPin, INPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  return;
}

