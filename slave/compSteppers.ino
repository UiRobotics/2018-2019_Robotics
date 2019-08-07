#include <Stepper.h>

#define STEPS 5000  // theoretically the number of steps on the stepper

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's attached to
Stepper stepper(STEPS, 26, 5);

void setup() {
  stepper.setSpeed(200); // in rpm if you set steps correctly (I didn't, but who cares)
}

int val = 90; // will need to come from controller
int mappedSpeed = 0;
float speedModifier = 1; // the knob that dampens stepper speed

void loop() {
  if (val > 94) {
    mappedSpeed = map(val, 94, 180, 0, 300);
    stepper.setSpeed(mappedSpeed / speedModifier);
    stepper.step(10);
  }
  else if (val < 86) {
    mappedSpeed = map(val, 0, 86, 0, 300);
    stepper.setSpeed(mappedSpeed);
    stepper.step(-10);
  }
}
