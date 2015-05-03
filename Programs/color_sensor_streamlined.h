/*
 ********************************
   MEC 550 Maze Solving Robot
     Color Reading Program
    Version 2 May 2, 2015
 *******************************
 
 ********************************
        Change History
 ********************************
Version 1 4/22/15
- Created base version of the program
- Need to annotate the program with comments more

Version 2 5/2/15
- Optimized dynamic memory use (granted it was 1% before, but still)
 * Done by changing variables S0, S1, S2, S3 from "int" variables to "#define" variables
 *********************************
        End Change History
 *********************************
*/

#define S0 8
#define S1 9
#define S2 11
#define S3 12
char outputPin = 10;
#define LED 13

void setup(){
  pinsetup();

}

void loop() {
detectColor(outputPin);
delay(1000);
}

int detectColor(char outputPin){
  int red = colorRead(outputPin, 1, 1); // detect % red
  int green = colorRead(outputPin, 2, 1); // detect % green
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
