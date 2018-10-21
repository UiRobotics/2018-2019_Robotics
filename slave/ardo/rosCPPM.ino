#include <Servo.h>
#include <AccelStepper.h>

Servo wheelsR; // Right side motors
Servo wheelsL; // left side motors
AccelStepper S1(1,6,7);
AccelStepper S2(1,4,5);
AccelStepper S3(1,2,3);
AccelStepper S4(1,0,1);

void setup() {
  wheelsR.attach(10, 1000, 2000);
  wheelsL.attach(11, 1000, 2000);

  S1.setMaxSpeed(400);
  S2.setMaxSpeed(400);
  S3.setMaxSpeed(400);
  S4.setMaxSpeed(400);
  S1.setAcceleration(400);
  S2.setAcceleration(400);
  S3.setAcceleration(400);
  S4.setAcceleration(400);
  S1.setSpeed(100);
  S2.setSpeed(100);
  S3.setSpeed(100);
  S4.setSpeed(100);
}

void loop() {

  wheelsR.write(90); //send speed to right wheels, 90-180 is backwards currently
  wheelsL.write(90); //send speed to left wheels

  //SFwd.runSpeedToPosition();
  S1.runSpeed();
  S2.runSpeed();
  S3.runSpeed();
  S4.runSpeed();
  //delay(100);
}
