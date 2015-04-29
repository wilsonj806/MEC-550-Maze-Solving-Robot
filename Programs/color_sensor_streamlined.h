/*
 ********************************
   MEC 550 Maze Solving Robot
     Color Reading Program
    Version 1 April 22, 2015
 *******************************
 
 ********************************
        Change History
 ********************************
Version 1 4/22/15
- Created base version of the program
- Need to annotate the program with comments more
 *********************************
        End Change History
 *********************************
*/

int S0 = 8;
int S1 = 9;
int S2 = 11;
int S3 = 12;
int outputPin = 10;
int LED = 13;

void setup(){
  pinsetup();
  delay(100);
}

void loop() {
detectColor(outputPin);
delay(1000);
}

int detectColor(int outputPin){
  float red = colorRead(outputPin, 1, 1); // detect % red
  float green = colorRead(outputPin, 2, 1); // detect % green
}
float colorRead(int outputPin, int color, boolean LEDstate){ // declare color read function as a float
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
void outputMode(int mode){
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
