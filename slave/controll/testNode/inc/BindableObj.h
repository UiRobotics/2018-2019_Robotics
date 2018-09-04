/*
 * BindableObj.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Joseph
 */

#ifndef BINDABLEOBJ_H_
#define BINDABLEOBJ_H_

#include "../lib/tcpS/PracticalSocket.h"
#include "../inc/macro.h"
#include <exception>
#include <thread>
#include <iostream>

namespace uiRobotics {

class BindableObj {
public:
	BindableObj(string name);
	void SetPortAndAddress(string address, unsigned short port);
	std::string getName(void);

	virtual ~BindableObj();

protected:
	virtual std::string HandleGetMsg(void* msg);
	virtual void ParallelCall();
	virtual void HandlException(std::exception& err);

	void MsgLoop(void);
	virtual void ShutDown();
	//not working virtual void SendMsgTo(char* address, void* msg);
private:
	TCPSocket* c_MsgClientTCP_Socket;
	std::string m_Name;
	std::thread* m_ThreadMsgRecv;
	bool m_Abort;
};

} /* namespace uiRobotics */

#endif /* BINDABLEOBJ_H_ */
