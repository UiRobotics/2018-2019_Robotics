/*
 * BindableObj.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: Joseph
 */

#include "BindableObj.h"

namespace uiRobotics {

BindableObj::BindableObj(std::string name)
	: c_MsgClientTCP_Socket(nullptr)
	, m_Name(name)
	, m_ThreadMsgRecv(nullptr)
	, m_Abort(false)
{


}

void BindableObj::SetPortAndAddress(std::string address, unsigned short port)
{

	c_MsgClientTCP_Socket = new TCPSocket(address, port);
	m_ThreadMsgRecv = new std::thread(&BindableObj::MsgLoop, this);
	m_ThreadMsgRecv->detach();
};

std::string BindableObj::getName()
{
	return m_Name;
}

void BindableObj::MsgLoop()
{

	bool notAbort = true;
	char buffer[MSG_MAX_BUFFER_SIZE];
	char sendBuffer[MSG_MAX_BUFFER_SIZE];
	while (notAbort)
	{
		c_MsgClientTCP_Socket->recv(buffer, MSG_MAX_BUFFER_SIZE);

		std::string sendstr = HandleGetMsg(buffer);
		cout << m_Name << "::" << buffer << endl;

		if(m_Abort)
		{
			std::strcpy(sendBuffer, MSG_SHUT_DOWN);
			notAbort = false;
		}
		else
		{
			std::strcpy(sendBuffer, sendstr.c_str());
		}

		std::cout << m_Name << "::" << sendBuffer << endl;

		c_MsgClientTCP_Socket->send(sendBuffer, MSG_MAX_BUFFER_SIZE);

		ParallelCall();
	}
}

std::string BindableObj::HandleGetMsg(void* msg)
{
	return std::string(MSG_CAN_SEND);
}

void BindableObj::ParallelCall()
{

}

void BindableObj::ShutDown()
{
	m_Abort = true;
}

void BindableObj::HandlException(std::exception &err)
{
	cerr << err.what() << endl;
	ShutDown();
}

BindableObj::~BindableObj()
{
	if(c_MsgClientTCP_Socket) delete c_MsgClientTCP_Socket;
}

} /* namespace uiRobotics */
