/*
 * msgParser.h
 *
 *  Created on: Feb 20, 2017
 *      Author: JJB07
 */

#ifndef LIB_TRANSTOOLDFORMAT_MSGPARSER_H_
#define LIB_TRANSTOOLDFORMAT_MSGPARSER_H_

#include <string>
#include <sstream>
#include "../../inc/macro.h"
#include "Modes.h"

namespace msgParser
{
	std::string TransToNewFormat(std::string msg);
	std::string TransToOldFormat(std::string msg);
	std::string MotToNewFormat(std::string msg);
};

#endif /* LIB_TRANSTOOLDFORMAT_MSGPARSER_H_ */
