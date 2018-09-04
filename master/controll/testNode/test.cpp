/*
 * test.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: JJB07
 */

//#include <iostream>
#include "inc/IDevice.h"
#include <iostream>
#include "lib/TransToOldFormat/msgParser.h"
#include "header/motor.h"
#include "header/SKit.h"
#include "lib/arduino-serial-lib.h"
#include "unistd.h"

 int main(){

	std::cout << "working" << std::endl;


	int fd=-1;
	fd = serialport_init("/dev/ttyACM0", 9600); //opening port
	(fd == -1) ? std::cout<< "couldn't open port for RC arduino! :(" << std::endl : std::cout<< "opened port " << std::endl;
	serialport_flush(fd);

	uiRobotics::IDevice* dev;
	char str[] = "6011";
	uiRobotics::CREATE_UI_ROBOTICS_DEVICE(&dev, str);
	motor motor("/dev/ttyACM1", 115200);
	//uiRobotics::SKit skit(8800);

	dev->Bind(&motor);
	dev->SetServerPort(7017);

	dev->Start();
	//TCPServerSocket sock(7090);
	sleep(1);
	//TCPSocket* s = sock.accept();
	TCPSocket revS("0.0.0.0", 7017);
	char buffer[255];
	while(true)
	{

		int read = serialport_read_until(fd, buffer, '\n', 255, 10000);
		//s->recv(buffer, 255);
		if(read != -1 && buffer[0]=='m'){

			this_thread::yield();
			//std::string str;//("motor_controller:set_servo1-90;");//(buffer);//= msgParser::TransToNewFormat(std::string(buffer));
			//std::cin >> str;
			std::string str(buffer);
			std::cout << str << std::endl;
			//std::cout << msgParser::TransToOldFormat(str) << std::endl;

			revS.send(str.c_str(), MSG_MAX_BUFFER_SIZE);
			//char buffer[MSG_MAX_BUFFER_SIZE];
			//std::cin >> buffer;
			revS.recv(buffer, MSG_MAX_BUFFER_SIZE);
			this_thread::yield();
			/*while(true)
			{
			this_thread::yield();
			}*/
		}
	}
}
