/*
 * SKit.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: thor
 */

#include "../header/SKit.h"

namespace uiRobotics {

SKit::SKit(unsigned int port)
	: uiRobotics::BindableObj("skit")
	, _m_port(port)
	, _m_socket(nullptr)
	, _m_socket_pi(nullptr)
{

	_m_socket = new TCPServerSocket(_m_port);

	_m_socket_pi = _m_socket->accept();
}

std::string SKit::HandleGetMsg(void* msgraw)
{

	_m_socket_pi->send((char*)msgraw, strlen((char*)msgraw) + 1);
	char* msgr = (char*)malloc(MSG_MAX_BUFFER_SIZE);
	_m_socket_pi->recv(msgr, MSG_MAX_BUFFER_SIZE);
	std::string re(msgr);
	free(msgr);

	return re;
}

SKit::~SKit()
{
	_m_socket->cleanUp();
	delete(_m_socket_pi);
	delete(_m_socket);
}

} /* namespace uiRobotics */
