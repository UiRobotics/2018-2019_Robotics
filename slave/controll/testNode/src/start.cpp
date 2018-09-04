/*
 * start.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Joseph
 */
#include "../inc/IDevice.h"
#include "../header/Device.h"

namespace uiRobotics
{

	void CREATE_UI_ROBOTICS_DEVICE(IDevice** dev, char* localPort)
	{
		*dev = new Device(localPort);
	}

	exception::exception(std::string what) : std::exception()
		, m_What(what)
	{


	}

	std::string exception::what()
	{
		return m_What;
	}

	exception::~exception()
	{

	}
}

namespace msgParser
{

	string FindDesName(string msg){

		std::stringstream ss(msg);
		std::string name;
		char c;

		while(ss.peek() != ':' && ss.peek() != ';')
		{
			ss >> c;
			name.push_back(c);
		};

		return name;
	}

	string FindCommand(string msg)
	{
		std::stringstream ss(msg);
		std::string command;
		char c;

		while(ss.peek() != ':')
		{
			ss >> c;
		}

		ss >> c;
		while(ss.peek() != '-' && ss.peek() != ';')
		{
			ss >> c;
			command.push_back(c);
		}

		return command;
	}

	string FindVal(string msg)
	{
		std::stringstream ss(msg);
		std::string val;
		char c;

		while(ss.peek() != '-')
		{
			ss >> c;
		}

		ss >> c;
		while(ss.peek() != ';')
		{
			ss >> c;
			val.push_back(c);
		}

		return val;
	}
}
