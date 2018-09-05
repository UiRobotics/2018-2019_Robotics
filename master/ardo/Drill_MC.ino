#include <Servo.h>
// Sabertooth 2x32
// Dipswitches 2 and 5 are up
// commands: drill - 0/1 for off/on
//           servo - 0/1 for close/open
//           LAD (linear actuator) - 0/1 for extend/retract and 2 for pause;
Servo LAD;
Servo motor;
Servo servo;
void setup() {
   LAD.attach(9);
   motor.attach(8);
   servo.attach(7);
   Serial.begin(9600);
}

void loop() {
  String data = Serial.readString();
  String command;
  int value;
  
  if (data[0] == 'I') {
    data = rmSemi(data); // removes Idevice: and similar I: things
  }
  data = rmSemi(data); // removes the destination
  while (data.length() > 0) {
    data = parseM(data, command, value);
    if (command == "drill") {
      motor.write(90 - (20 * value)); // 90 and 70
    }
    else if (command == "LAD") {
      if (value == 2) {
        LAD.write(90);
      }
      else {
        LAD.write(40 + (80 * value));
      }
    }
    else if (command == "servo") {
      servo.write(20 + (135 * value)); //20 and 155
    }
  }
}

String parseM(String data, String &command, int &value) {
  command = "";
  value = 0;
  int i = 0;
  while (data[i] != '-') {
    command += data[i];
    i++;
  }
  String temp = "";
  i++;
  while (data[i] != ':' && data[i] != ';') {
    temp += data[i];
    value = temp.toInt();
    i++;
  }
  if (data[i] == ';') {
    for (i; i < (data.length())-1; i++) {
    }
  }
  data.remove(0,i+1);
  return data;
}

String rmSemi(String inputString) {
  while ((inputString[0] != ':') && inputString.length() > 0) {
    inputString.remove(0,1);
  }
  inputString.remove(0,1);
  return inputString;
}


//////////////////////////////////////////////////////////////////////////////
// motor 90-98 is stopped
// lad potentiometer is 100-990
// lad wires: 
void moveto(float input) {
  float data;
  data = readpot();
  while (data < input - .02 || data > input + .02) {
    data = readpot();
    if (data < input - .02) {
      LAD.write(40);
    }
    else if (data > input + .02) {
      LAD.write(120);
    }
    else {
      LAD.write(90);
    }
  }
}

float readpot() {
  float x = map(analogRead(A1), 100, 990, 0, 3690);
  float y = x / 1000;
  float z = constrain(y, 0, 3.69);
  return z;
  delay(300);
}
