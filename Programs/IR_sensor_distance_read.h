/* 
*********************************
   MEC 550 Maze Solving Robot
    IR sensor distance read
     Version 1 May 2, 2015
*********************************

************************
Change History
************************
5/2/2015- Version 1
-Created base version
************************
End Change History
************************

This program includes the calibration curve for the IR sensor

*/

#define irsensor 0

void setup(){
}
void loop(){
}

int distanceRead(float raw){
raw = analogRead(irsensor);
float val = 0.0049 * raw;
int distance = 1 * pow(10,-14)*pow(val,6)-pow(2,-11)*pow(val,5)
+pow(1,-18)*pow(val,4)-pow(4,-6)*pow(val,3)+pow(8,-4)*pow(val,2)+pow(-8.77,-2)*val+4.97;
return distance;
}
