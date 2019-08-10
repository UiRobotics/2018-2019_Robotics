//#include <Stepper.h>
#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt8MultiArray.h>

#define STEPS 5000  // theoretically the number of steps on the stepper

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's attached to
float val[6] = {90, 90, 90, 90, 90, 90};
//Stepper stepper1(STEPS, 20, 2);
//Stepper stepper2(STEPS, 22, 3);
//Stepper stepper3(STEPS, 24, 4);
//Stepper stepper4(STEPS, 26, 5);

Servo servo1;
Servo servo2;

void messageCb(const std_msgs::UInt8MultiArray& stepper_msg)
{

  //Serial.println(val[1]);
  
  //set_stepper(val[0], &stepper1);
  //set_stepper(val[1], &stepper2);
  //set_stepper(val[2], &stepper3);
  //set_stepper(val[3], &stepper4);

  //set_CIM(val[4], &servo1);
  //set_CIM(val[5], &servo2);

  an
  //servo1.write(val[1]);
  //servo2.write(val[1]);
  //analogWrite(7, val[1]);
  //analogWrite(8, val[1]);
}


ros::NodeHandle_<ArduinoHardware, 10, 15, 128, 256> nh;
ros::Subscriber<std_msgs::UInt8MultiArray> sub("RC_Drive_Mapped", &messageCb);

void setup() {
  //Serial.begin(57600);
  servo1.attach(7);
  servo2.attach(8);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  //stepper1.setSpeed(200);
  //stepper2.setSpeed(200);
  //stepper3.setSpeed(200);
  //stepper4.setSpeed(200);
  nh.initNode();
  nh.subscribe(sub);
}
int mappedSpeed = 0;
float speedModifier = 1; // the knob that dampens stepper speed

/*void set_stepper(float val, Stepper* stepper)
{
   if (val > 94) {
    mappedSpeed = map(val, 94, 180, 0, 300);
    stepper->setSpeed(mappedSpeed / speedModifier);
    stepper->step(10);
  }
  else if (val < 86) {
    mappedSpeed = map(val, 0, 86, 0, 300);
    stepper->setSpeed(mappedSpeed);
    stepper->step(-10);
  }
}*/

void set_CIM(float val, Servo* servo)
{
  if (val > 94) {
    float val_map = map(val, 0, 180, 30, 120);
    servo->write(val_map); 
  }
  else if (val < 86) {
    float val_map = map(val, 0, 180, 30, 120);
    servo->write(val_map);
  }
}

void loop() {
  nh.spinOnce();
  delay(10);
}
