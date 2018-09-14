/*
 * Cppm_Sabertooth.ino
 * 
 * This code is meant to be loaded on to the Arduino that controls the Sabertooth motor controller.
 */

#include <TimerOne.h>
#include <Servo.h>
unsigned long int a,b,c;
int x[19],ch1[19],ch[9],i;

int numofloops = 100; //2080 full rotation
int SM_speed = 200;

int drive1 = 90; // 90 is stop, 0 reverse, 180 foward.
int drive2 = 90;
int UsableSig = 90;

int angle = 0;
int anglea[25];
int curangle = 0;
int dirs = HIGH;
int counter = 0; 

int mot1 = 90;
int mot1a[25];
int mot2 = 90;
int mot2a[25];

Servo ST1, ST2; // read SabertoothSweep comments for details

void setup() {
  
  initarr(&mot1a[0]);
  initarr(&mot2a[0]);
  initarr(&anglea[0]);

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  Timer1.initialize(2500);
  Timer1.attachInterrupt(callback);
  
  ST1.attach( 10, 1000, 2000);
  ST2.attach(11, 1000, 2000); 
  
  Serial.begin(115200);
  Serial.setTimeout(25);
}

void initarr(int arr[])
{
  for (int i = 0; i < 25; i++)
    arr[i] = 90;
}

void loop() {
  String data = Serial.readString();
  String command;
  int value;
  
  if ( data[0] == 'I') {
      data = rmSemi(data); // removes Idevice: and similar I: things
    }
    data = rmSemi(data); // removes the destination
    while (data.length() > 0) {
      data = parseM(data, command, value);
      // put command and value switches here
        if (command == "set_servo1") {
          mot1 = value;
          
        }
        if (command == "set_servo2")
        {
          //push(&mot2a[0], value);
          mot2 = value;
        }  
        int pos;
      int pul_motor;
      int dir_motor;
      int speed_input = 3000;
      float degree;
      Serial.println("good");
      if (command == "set_steppermotor1")
      {
        angle = value - 90;
      }
      else if (command == "set_steppermotor2")
      {
        angle = value - 90;
      }
      //delay(25);
    }

  //ST1.write(drive1); //send data to motor 1 //pin 9 and 10.
  //Serial.print(drive1);
  //Serial.print(" ");
  //ST2.write(drive1); //send data to motor 2
  //Serial.println(drive2);
  //Serial.println(mot1);
  delay(100);
  ST1.write(mot1);
  ST2.write(mot1);
}

int temp[25];
void push(int data[], int val)
{
  for(int i = 1; i < 25; i++)
    temp[i-1] = data[i];
   temp[24] = val;
   
   for(int i = 0; i < 25; i++)
   {
     data[i] = temp[i];
     Serial.println(data[i]);
   } 
}

int avg(int arr[])
{
  float avg = 0;
  
  for(int i = 0; i < 25; i++)
  {
    avg += (float)arr[i]/25;
  }
  
  return (int)avg;
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
    for (i; i < (data.length())-1;i++) {
    }
  }
  data.remove(0,i+1);
  return data;
}

String rmSemi(String inputString) {
  int i = 0;
  while ((inputString[0] != ':') && inputString.length() > 0) {
    inputString.remove(0,1);
    i++;
  }
  inputString.remove(0,1);
  return inputString;
}

void callback()
{
  curangle=(float)counter*360/10000;
  //Serial.println(abs(1000*((float)angle) / 360));
  if(abs(curangle - angle) <= 2)
  {
    curangle = angle;
    //Serial.println(counter);
    //Serial.println(1000*(float)angle / 360);
    return;
  }
  else{
    //Serial.println("good");
    if(angle > curangle)
    {
      dirs=HIGH;
      digitalWrite(5, dirs);
      counter++; 
    }else
    {
      dirs=LOW;
      digitalWrite(5, dirs);
      counter--;
    }
    digitalWrite(6, digitalRead( 6 ) ^ 1 );
  }
}

