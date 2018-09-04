/*
 * msgParser.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: JJB07
 */
#include "msgParser.h"
#include "../../inc/macro.h"
#include "../../inc/IDevice.h"

namespace msgParser
{

	std::string MotToNewFormat(std::string msg)
	{
		std::stringstream ss(msg);
		std::string out;
		char c;
		ss >> c;
		ss >> c;
		ss >> c;

		switch(c)
		{
		case Mode::MOVE_FORWARD:
			out = "motor_controller:move_forward";
			break;
		case Mode::MOVE_REVERSE:
			out = "motor_controller:move_back";
			break;
		case Mode::TURN_LEFT:
			out = "motor_controller:turn_left";
			break;
		case Mode::TURN_RIGHT:
			out = "motor_controller:turn_right";
			break;
		default:
			return "system:unknown;";
		}

		out.push_back('-');
		out.push_back(ss.get());
		out.push_back(ss.get());
		out.push_back(ss.get());
		out.push_back(';');

		return out;
	}

	std::string TransToNewFormat(std::string msg)
	{

		std::stringstream ss(msg);
		char c;

		ss >> c;
		ss >> c;


		std::string newF;

		switch(c)
		{
		case 'M':
			newF = MotToNewFormat(msg);
			break;
		case 'S':
			break;
		case 'I':
			break;
		default:
			break;
		}

		return newF;
	}

	std::string TransToOldFormat(std::string msg)
	{

		std::stringstream ss(msg);
		std::string name = msgParser::FindDesName(msg);

		std::string old;
		old.push_back('[');
		if(name.compare(std::string("motor_controller")) == 0)
		{
			old.push_back('M');

			std::string command = msgParser::FindCommand(msg);
			if(command.compare("move_forward") == 0)
			{
				old.push_back(Mode::MOVE_FORWARD);
			}
			else if(command.compare("move_back") == 0)
			{
				old.push_back(Mode::MOVE_REVERSE);
			}
			else if(command.compare("turn_left") == 0)
			{
				old.push_back(Mode::TURN_LEFT);
			}
			else if(command.compare("turn_right") == 0)
			{
				old.push_back(Mode::TURN_RIGHT);
			}

			std::string val = msgParser::FindVal(msg);
			char c;
			old.append(val);
		}
		else
		{
			throw uiRobotics::exception("can't convert to old format.");
		}
		old.push_back(']');
		return old;
	}
};
