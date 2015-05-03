/*
 ****************************
  MEC 550 Maze Solving Robot
  Maze Solving Pseudocode A*
   Version 1 May 2, 2015
 ****************************

********************
   Change History
********************
5/2/2015 - Version 1
- Created base version
- Need to add a provision for the robot figuring where it is in the maze
- Need to add a provision for updating the robot's current position
********************
End Change History
********************
*/

#include <MotorDriver.h>
#include<Servo.h>

#define irsensor1 0
#define irsensor2 1
#define echopin 1
#define trigpin 2
#define servopin 6
Servo claw;
float rightdistance, leftdistance, raw1, raw2;
int duration, frontdistance, color, navcheck;

// start the navigation matrix
// start i as the number of rows and j as the number of columns
char navmatrix[8][8];



/* mark simply as
 state 0 = color read/ bearing reset
state 1 = check distance
state 2 = decide what to do
state 3 = right turn
state 4 = left turn
state 5 = stragithaway
state 6 = 180° turn
state 7 = dead end
state 8 = ball grabbing thing
state 9 = terminal state
*/

/* dead end: value of either 0 or one
turn counter: value range of 0-4
bearing: value range of 0-4
pos: value range of 0-400
*/
char state, deadend, turncounter, bearing, pos,i,j;

void setup(){
pinMode(echopin,INPUT);
pinMode(trigpin, OUTPUT);
//TSC3200();
claw.attach(servopin);
// start declaring where the robot starts
}

void loop(){
switch(state){
case 1:
/* insert all IR sensor reading shit
 insert all ultrasonic reading shit
 if left turn available
  matrixwrite(state = left turn)

*/
navmatrix[i][j]=matrixwrite(state);
break;

case 2:
//
break;

case 3:
//
break;

case 4:
//
break;

case 5:
//
break;

case 6:
//
break;

case 7:
//
break;

case 8:
//
break;

case 9:
//
break;
}
}

/* 
 In Arduino/ C/ C++, array elements cannot be called like in MATLab (in MATLab it's like array(i,j)= whatever)
 In C/ C++, it starts the first index at 0 and then each element gets a call number (calling the (15,10)element for say
 a 20 by 20 matrix is done via array(289) = whatever's there)
  This function calculates what the value of the index is given the i-th row and j-th column
 */
 
/*
 This function writes the state of a thing based on the state, bearing, and whether or not it registers a dead end
 NOTE: CANNOT HAVE navcheck
*/
char matrixwrite(char state){
char i,j;
switch(state){
case 3:
switch(bearing){
case 0:
if (deadend == 0){
char navcheck = 1;;
return navcheck;
}
else if (deadend ==1){
char navcheck = 0;
return navcheck;
}
break;

case 1:
if (deadend == 0){
char navcheck = 1;
return navcheck;
}
else if (deadend == 1){
char navcheck = 0;
return navcheck;
}
break;

case 2:
if (deadend == 0){
char navcheck = 1;
return navcheck;
}
else if (deadend == 1){
char navcheck = 0;
return navcheck;
}
break;

case 3:
if (deadend == 0){
char navcheck = 1;
return navcheck;
}
else if (deadend == 1){
char navcheck = 0;
return navcheck;
}
break;

}
case 4:
switch(bearing){
case 0:
if (deadend == 0){
char navcheck = 1;
return navcheck;
}
else if (deadend == 1){
char navcheck = 0;
return navcheck;
}
break;

case 1:
if (deadend == 0){
char navcheck = 1;
return navcheck;
}
else if (deadend == 1){
char navcheck = 0;
return navcheck;
}
break;

case 2:
if (deadend == 0){
char navcheck = 1;
return navcheck;
}
else if (deadend == 1){
char navcheck = 0;
return navcheck;
}
break;

case 3:
if (deadend == 0){
char navcheck = 1;
return navcheck;
}
else if (deadend == 1){
char navcheck = 0;
return navcheck;
}
break;
}
case 5:
switch(bearing){
case 0:
if (deadend == 0){
char navcheck = 1;
return navcheck;
}
else if (deadend == 1){
char navcheck = 0;
return navcheck;
}
break;

case 1:
if (deadend == 0){
char navcheck = 1;
return navcheck;
}
else if (deadend == 1){
char navcheck = 0;
return navcheck;
}
break;

case 2:
if (deadend == 0){
char navcheck = 1;
return navcheck;
}
else if (deadend == 1){
char navcheck = 0;
return navcheck;
}
break;

case 3:
if (deadend == 0){
char navcheck = 1;
return navcheck;
}
else if (deadend == 1){
char navcheck = 0;
return navcheck;
}
break;
}
}
}
