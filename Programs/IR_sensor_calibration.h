/*
 ******************************
   MEC 550 Maze Solving Robot
     IR Sensor Calibration
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
 
 This program uses an IR sensor and an ultrasonic sensor in order to calibrate the IR sensor
 
 */
 
// define the infrared sensor input pin on the Arduino
// Also note that "#define" does not actually use memory, very handy
#define infraredPin 0
#define echoPin 4
#define trigPin 12
// define the output of the infrared as a floating point variable
int raw, mm;
word duration;
float val;

void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop(){
  raw = analogRead(infraredPin);
  // remember that you have to multiply the analogRead() value by 0.0049 due to the change from 10 bit to a voltage scheme
  // resolution = (5V-0V)/(2^10) is approximately 0.0049 V
  val = raw*0.0049;
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 // Output a low frequency thing to allow for a clean higher freqency reading
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 // High frequency waveform that will be read by the sensor
 duration = pulseIn(echoPin, HIGH);
 // pulseIn reads the high frequency pulse from echoPin as a time
 mm = duration/5.8;
 Serial.println("Sensor distance");
 Serial.println(mm);
 Serial.print("Raw voltage value: " );
 Serial.println(val);
 delay(1000);
}
