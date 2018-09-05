#include <Servo.h>
#include <math.h>
Servo servo1;
Servo servo2;

void setup () {
  servo1.attach(9);
  servo2.attach(8);
  Serial.begin(9600);
}

//motor values from 40 to 160

void loop() {
  float input1,input2;
  input1 = 2.4;
  input2 = 2.4;
  
  //moveto(input1,input2);
  float testangle1 = 40, testangle2 = 40;
  test((testangle1*M_PI/180),(testangle2*M_PI/180));

  
}

//yellow to A1
//blue 5v
//white ground
//servo1 has red wire in m1a
//servo2 has red wire in m2b

float readpot1 () {
  int whiteVal = analogRead(A1);

  float x = map(analogRead(A1), 26, 876, 0, 3690);
  float y = x / 1000;
  float z = constrain(y, 0, 3.69);

  Serial.println(z);
  return z;

  delay(300);
}

float readpot2 () {
  int whiteVal = analogRead(A2);

  float x = map(analogRead(A2), 127, 980, 0, 3690);
  float y = x / 1000;
  float z = constrain(y, 0, 3.69);

  Serial.println(z);
  return z;

  delay(300);
}

void moveto(float input1, float input2) {
  float data1, data2;
  data1 = readpot1();
  data2 = readpot2();
  while (data1 < input1 - .02 || data1 > input1 + .02 || data2 < input2 - .02 || data2 > input2 + .02) {
    data1 = readpot1();
    data2 = readpot2();
    if (data1 < input1 - .02) {
      servo1.write(120);
    }
    else if (data1 > input1 + .02) {
      servo1.write(60);
    }
    else {
      servo1.write(90);
    }

    if (data2 < input2 - .02) {
      servo2.write(120);
    }
    else if (data2 > input2 + .02) {
      servo2.write(60);
    }
    else {
      servo2.write(90);
    }
  }
}

void test(float angle1, float angle2){
  float A = 15;
  float B = 17;
  float AL1;
  float AL2;
  float ActuatorLengthminimum = 10.6995;

  AL1 = sqrt((A*A + B*B) - (2*A*B*cos(angle1))) - ActuatorLengthminimum;
  AL2 = sqrt((A*A + B*B) - (2*A*B*cos(angle2))) - ActuatorLengthminimum;
  moveto(AL1,AL2); 
  
}




