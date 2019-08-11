#include <TimerOne.h>
#include <Stepper.h>
#include <Servo.h>
#include <sbus.h>

#define STEPS 5000  // theoretically the number of steps on the stepper

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's attached to
float val[6] = {90, 90, 90, 90, 90, 90};
//Stepper stepper1(STEPS, 2, 5);
//Stepper stepper2(STEPS, 4, 6);

Servo servo1;
Servo servo2;

SBUS sbus;

float steppers = 90;
float last_steppers = 90;
float last_moter = 90;

void setup() {
  //Serial.begin(57600);
  
  servo1.attach(9);
  servo2.attach(10);
  //stepper1.setSpeed(200);
  //stepper2.setSpeed(200);
  //stepper3.setSpeed(200);
  //stepper4.setSpeed(200);
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  sbus.begin(3, sbusNonBlocking);
  Serial.begin(9600);
  //Timer1.initialize(500);
  //Timer1.attachInterrupt(stepint);
}
int mappedSpeed = 0;
float speedModifier = 1; // the knob that dampens stepper speed

void set_stepper(float val, Stepper* stepper)
{
   if (val > 100) {
    mappedSpeed = (int)((val - 987) * (180) / (2011 - 987));
    stepper->setSpeed(mappedSpeed / speedModifier);
    stepper->step(10);
  }
  else if (val < 82) {
    mappedSpeed = (int)((val - 987) * (180) / (2011 - 987));
    stepper->setSpeed(mappedSpeed);
    stepper->step(-10);
  }
}

void set_CIM(float val, Servo* servo)
{
  if (val > 100) {

    if( last_moter - val > 20)
        return;
    float val_map = (int)((val - 987) * (180) / (2011 - 987));
    if(val_map > 0)
      servo->write(val_map);
  }
  else if (val < 82) {
    float val_map = (int)((val - 987) * (180) / (2011 - 987));
    servo->write(val_map);
  }
  else
  {
    servo->write(90);  
  }
}

void stepint()
{
  int del = 20;
  float val = steppers;
  Serial.println(val);

  if(last_steppers - steppers > 20)
    return;

  if (val>0)
  {
  
    if (val > 130) {
      //set direction
      digitalWrite(2,HIGH);
      digitalWrite(4,HIGH);
  
      //move
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delayMicroseconds(del);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      delayMicroseconds(del);
    }
    else if (val < 50) {
          //set direction
      digitalWrite(2,LOW);
      digitalWrite(4,LOW);
  
      //move
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delayMicroseconds(del);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      delayMicroseconds(del);
    }
  }
}

void loop() {
  
  steppers = (float)(((float)sbus.getChannel(4) - 987) * (180) / (2011 - 987));
  int moter = sbus.getChannel(3);
  int moter2 = sbus.getChannel(2);

  set_CIM(moter2, &servo1);
  set_CIM(moter, &servo2);

  //set_stepper(stepper, &stepper1);
  //set_stepper(stepper, &stepper2);
  stepint();

  last_steppers = steppers;
  last_moter = moter;
  delayMicroseconds(20);
}
