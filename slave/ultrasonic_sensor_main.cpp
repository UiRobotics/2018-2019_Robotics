#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Float32MultiArray.h"

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "thread"
#include "mutex"
#include "vector"

ros::Publisher g_rc_mapped_pub;
std::thread* g_RC_PubThread = 0x00000;

std_msgs::Float32MultiArray g_UltrasonicInput;



/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void RC_Com_Callback(const std_msgs::Float32MultiArray::ConstPtr& ch)
{
	// map channels 
	std::vector<float> sensorsTemp(ch->data.begin(), ch->data.end());

	

}

void Pub_Thread()
{

  ros::Rate loop_rate(100);

  while(ros::ok())
  {
    g_RC_Mapper_Mutex.lock();
    g_rc_mapped_pub.publish(g_UltrasonicInput);
    g_RC_Mapper_Mutex.unlock();

    ros::spinOnce();
    loop_rate.sleep();
  }

}

void cleanUp()
{
  delete g_RC_Mapper_Mutex;
  delete g_RC_PubThread;
  delete g_rc_mapped_pub;
}

int main(int argc, char **argv){

 	g_RC_Mapper_Mutex = new std::mutex();
	ros::init(argc, argv, "Ultrasonic_Sensor");
	ros::NodeHandle n;

	g_rc_mapped_pub = n.advertise<std_msgs::Float32MultiArray>("Ultrasonic_Sensor", 1000);
	ros::Subscriber sub = n.subscribe("RC_Com", 1000, RC_Com_Callback);
	
	g_UltrasonicInput.layout.dim = std::vector<std_msgs::MultiArrayDimension>(1);
	g_UltrasonicInput.layout.dim[0].size = 6;
	g_UltrasonicInput.layout.dim[0].stride = 1;
	g_UltrasonicInput.layout.dim[0].label = "Ultrasonic_Sensor";
	g_UltrasonicInput.data = std::vector<float>(3);
	g_RC_PubThread = new std::thread(Pub_Thread);

	g_RC_PubThread->join();

	cleanUp();

	return 0;

}
