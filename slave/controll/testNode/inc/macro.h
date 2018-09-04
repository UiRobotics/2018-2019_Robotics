/*
 * macro.h
 *
 *  Created on: Jan 29, 2017
 *      Author: Joseph
 */

#ifndef MACRO_H_
#define MACRO_H_

#include <string>
#include <sstream>

#define MSG_MAX_BUFFER_SIZE 3000
#define MSG_SHUT_DOWN "system::shut_down;"
#define MSG_CAN_SEND  "system::can_send;"

namespace msgParser
{

	extern std::string FindDesName(std::string msg);
	extern std::string FindCommand(std::string msg);
	extern std::string FindVal(std::string msg);

}

#endif /* MACRO_H_ */
