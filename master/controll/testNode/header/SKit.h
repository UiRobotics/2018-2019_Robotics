/*
 * SKit.h
 *
 *  Created on: Jan 28, 2018
 *      Author: thor
 */

#ifndef INC_SKIT_H_
#define INC_SKIT_H_

#include "../inc/BindableObj.h"


namespace uiRobotics {

class SKit: public BindableObj {
public:
	SKit(unsigned int port);

	virtual std::string HandleGetMsg(void* msg);

	virtual ~SKit();
private:
	unsigned int _m_port;
	TCPServerSocket* _m_socket;
	TCPSocket* _m_socket_pi;
};

} /* namespace uiRobotics */

#endif /* INC_SKIT_H_ */
