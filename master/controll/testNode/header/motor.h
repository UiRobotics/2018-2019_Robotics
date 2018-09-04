#ifndef ARDUINO_H_
#define ARDUINO_H_
#include <iostream>
#include "../lib/arduino-serial-lib.h"
#include "../inc/BindableObj.h"
#include "../inc/macro.h"
#include "../lib/TransToOldFormat/msgParser.h"

class motor : public uiRobotics::BindableObj{
	
	public:
		/**
		 *
		 */
		motor(const char* port, int band_rate);
		/**
		 * Description: writes the string to the arduino
		 * Input: the message to be written
		 */
		virtual std::string HandleGetMsg(void* msg);
		virtual std::string ToArduinoFormat(std::string msg);

	private:
		int fd;
};

#endif
