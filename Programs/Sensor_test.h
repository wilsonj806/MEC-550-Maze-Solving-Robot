/*
 ********************************
   MEC 550 Maze Solving Robot
    Ultrasonic Test Program
    Version 1 April 9, 2015
 *******************************
 
 ********************************
        Change History
 ********************************
Version 1 4/9/15
- Created base version of the program
 *********************************
        End Change History
 *********************************

 Basic range finding program

*/
#define echoPin 4
#define trigPin 12

/* Set variables:
 * One variable is for the digital input or the "Echo" pin on the ultrasonic
 * The other is the "Trigger" pin which sends an ultrasonic pulse
 * const int makes the variable read only rather than read and write
 */
 word duration;
 int delD, dnom,dl;
void setup(){
 Serial.begin(9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 // Write the waveform triggering pin as an OUTPUT
 // Write the echo pin as an INPUT
}

void loop(){

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
 dnom = 24;
 delD = dnom-dl;
 Serial.print("Separation distance");
 Serial.println(delD);
 Serial.println("Sensor distance");
 Serial.println(dl);
 delay(5000);
 // Convert time to length

}

// The side with the Vcc pin should be more forwards on any robot
