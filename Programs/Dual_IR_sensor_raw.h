/*
 ******************************
   MEC 550 Maze Solving Robot
     Dual IR Sensor Read
    Version 1 May 2, 2015
 ******************************
 
 *********************
    Change History
 *********************
 Version 1 - 5/2/15
 - Created base version
 
 **********************
   End Change History
 **********************
 
 This program reads voltage from two IR sensors
 One sensor is placed on the right, the other on the left
 
 */
 
// define the infrared sensor input pin on the Arduino
// Also note that "#define" does not actually use memory, very handy
#define infraredPin1 0
#define infraredPin2 2
int navmatrix[20][20];
// define the output of the infrared as a floating point variable
int raw1, raw2;
float val1, val2;

void setup(){
  Serial.begin(9600);
}

void loop(){
  raw1 = analogRead(infraredPin1);
  raw2 = analogRead(infraredPin2);
  // remember that you have to multiply the analogRead() value by 0.0049 due to the change from 10 bit to a voltage scheme
  // resolution = (5V-0V)/(2^10) is approximately 0.0049 V
  val1 = raw1*0.0049;
  val2 = raw2*0.0049;
  Serial.println("Sensor 1 raw voltage value: " );
  Serial.println(val1);
  Serial.println("Sensor 2 raw voltage value: ");
  Serial.println(val2);
  Serial.println("  ");
  delay(1000);
}
