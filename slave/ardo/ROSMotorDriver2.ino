/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

// Use the following line if you have a Leonardo or MKR1000 
//#define USE_USBCON 

#include <sbus.h>
#include <ros.h>
#include <std_msgs/Int32MultiArray.h>

#define SBUS_PIN 0

ros::NodeHandle nh;

SBUS sbus;

std_msgs::Int32MultiArray channels;
ros::Publisher RC_Com("RC_Com", &channels);

void setup()
{
  nh.initNode();
  nh.advertise(RC_Com);
  
  channels.layout.dim = (std_msgs::MultiArrayDimension *)
  malloc(sizeof(std_msgs::MultiArrayDimension)*2);
  channels.layout.dim[0].size = 18;
  channels.layout.dim[0].stride = 1;
  channels.layout.dim[0].label = "RC_unmapped";
  
  channels.data = (long int *)malloc(sizeof(int long)*36);
  channels.data_length = 18;
  
  sbus.begin(SBUS_PIN, sbusBlocking);
}

void loop()
{
  
  if(sbus.waitFrame())
  {
    for(int i = 0; i < 18; i++)
      channels.data[i] = sbus.getChannel(i);
  }
  RC_Com.publish(&channels);
  
  
  nh.spinOnce();
  delay(10);
}
