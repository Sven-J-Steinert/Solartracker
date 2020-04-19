#include <Servo.h>

Servo rotate;
Servo tilt;

int rotVal = 90;
int tilVal = 100;

int topleft;
int topright;
int downleft;
int downright;

int average;

float factor = 0.02;
int delaytime = 10;
 
void moveit()
{   
  if (rotVal < 0){rotVal=0;}
  if (rotVal > 270){rotVal=270;}
  if (tilVal < 5){tilVal=5;}
  if (tilVal > 140){tilVal=140;}

  /*
  Serial.print(rotVal);
  Serial.print(" | ");
  Serial.print(average);
  Serial.print(" | ");
  Serial.println(tilVal);
  */
  
  rotate.write(rotVal);
  tilt.write(tilVal);
  delay(delaytime);
}

void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  rotate.attach(5);
  tilt.attach(6);
  
  rotate.write(rotVal);
  tilt.write(tilVal);

  // Serial.begin(9600);
  }

void loop() {
  topleft = analogRead(A2);
  topright = analogRead(A1);
  downleft = analogRead(A3);
  downright = analogRead(A0);
  
  average = roundf((topleft+topright+downleft+downright)/4); 
  if (average >= 900){factor = 0.02;}
  if ((average >= 700)and (average < 900)){factor = 0.05;}
  if ((average >= 600)and (average < 700)){factor = 0.10;}
  if ((average >= 500)and (average < 600)){factor = 0.15;}
  if (average < 500){factor = 0.2;}

  
  //topleft > topright
  if ( topleft - topright > roundf(topleft*factor) ) {
    rotVal = rotVal+1;
  }

  // downleft > downright
  if ( downleft - downright > roundf(downleft*factor) ) {
    rotVal = rotVal+1;
  }

  // topleft < topright
  if ( topright - topleft > roundf(topright*factor) ) {
    rotVal = rotVal-1;
  }

  // downleft < downright
  if ( downright - downleft > roundf(downright*factor) ) {
    rotVal = rotVal-1;
  }

  
  //topleft > downleft
    if ( topleft - downleft > roundf(topleft*factor) ) {
    tilVal = tilVal -1;
  }

//topright > downright
  if ( topright - downright > roundf(topright*factor) ) {
    tilVal = tilVal -1;
  }
  //topleft < downleft
  if ( downleft - topleft > roundf(downleft*factor) ) {
    tilVal = tilVal +1;
  }
// topright < downright
  if ( downright - topright > roundf(downright*factor) ) {
    tilVal = tilVal +1;
  }

  moveit();
}
