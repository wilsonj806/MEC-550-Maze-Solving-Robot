/*
 ******************************
   MEC 550 Maze Solving Robot
        IR Sensor Read
    May 2, 2015 Version 1
 ******************************
 
 *********************
    Change History
 *********************
 
 5/2/15
 - Created base version
 
 **********************
   End Change History
 **********************
 
 This program uses an IR sensor and spits out a voltage
 
 */
 
// define the infrared sensor input pin on the Arduino
// Also note that "#define" does not actually use memory, very handy
#define infraredPin 0
// define the output of the infrared as a floating point variable
int raw;
float val;

void setup(){
  Serial.begin(9600);
}

void loop(){
  raw = analogRead(infraredPin);
  // remember that you have to multiply the analogRead() value by 0.0049 due to the change from 10 bit to a voltage scheme
  // resolution = (5V-0V)/(2^10) is approximately 0.0049 V
  val = raw*0.0049;
  Serial.print("Raw voltage value: " );
  Serial.println(val);
  delay(1000);
}
