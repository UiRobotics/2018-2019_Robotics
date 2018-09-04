/*
 * Device.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Joseph
 */

#include "../header/Device.h"

Device::Device(char* localPort) : uiRobotics::IDevice()
	,m_Running(false)
	,m_msgSenderThread(nullptr)
	,s_LocalTCP_Socket(nullptr)
	,m_Port(std::atoi(localPort))
	,mc_BoundObj()
	,mc_RecvPort(NULL)
{
	s_LocalTCP_Socket = new TCPServerSocket(m_Port);
}

void Device::Release()
{
	this->~IDevice();
}

void Device::Start()
{
	m_Running.store(true, std::memory_order_seq_cst);
	m_msgSenderThread = new std::thread(&Device::msgSenderLoop, this);
}

void Device::Stop()
{
	shutDown();
	m_Running.store(false, std::memory_order_seq_cst);
	m_msgSenderThread->join();
	delete m_msgSenderThread;
}

void Device::startSocket(uiRobotics::BindableObj* obj, std::string address, unsigned short port)
{
	std::chrono::milliseconds timeSpan(1000);
	std::this_thread::sleep_for(timeSpan);

	obj->SetPortAndAddress(address, port);
}

void Device::Bind(uiRobotics::BindableObj* obj)
{

	bool running = m_Running.load(std::memory_order_seq_cst);
	if(running)
		throw uiRobotics::exception("Device is running can't bind");

	string address = s_LocalTCP_Socket->getLocalAddress();
	unsigned short port = s_LocalTCP_Socket->getLocalPort();

	TCPSocket* sock;

	std::thread thr(&Device::startSocket, obj, address, port);
	sock = s_LocalTCP_Socket->accept();
	thr.join();

	mc_BoundObj.emplace(obj->getName(), BoundObject(obj, sock));
}

void Device::SetServerPort(unsigned short port)
{
	bool running = m_Running.load(std::memory_order_seq_cst);
	if(running)
		throw uiRobotics::exception("Device is running can't setSererPort");

	mc_RecvPort = port;
}

bool Device::validMsg(std::string msg)
{
	return !(msg.compare(MSG_CAN_SEND) == 0);
}

void Device::msgSenderLoop()
{

	bool exchange = true;
	TCPServerSocket recvServerSocket(mc_RecvPort);
	while(m_Running.compare_exchange_strong(exchange, true, std::memory_order_seq_cst))
	{
		exchange = true;

		char rawData[MSG_MAX_BUFFER_SIZE];
		char sendBack[MSG_MAX_BUFFER_SIZE];
		TCPSocket* recvSocket = recvServerSocket.accept();
		std::cout << "IDevice::Got Connection\n" << endl;
		size_t recvSize = 1;
		std::string sendTo(";");

		while(recvSize > 0)
		{
			memset(rawData, 0, MSG_MAX_BUFFER_SIZE);
			memset(sendBack, 0, MSG_MAX_BUFFER_SIZE);

			if(sendTo.compare(";") == 0)
			{
				recvSize = recvSocket->recv(rawData, MSG_MAX_BUFFER_SIZE);
			}
			else
			{
				strcpy(rawData, sendTo.c_str());
				sendTo = ";";
			}

			std::cout << "IDevice::msg::" << rawData << endl;

			string msg(rawData);
			string desName = msgParser::FindDesName(msg);

			std::unordered_map<std::string, BoundObject>::iterator it;
			for (it = mc_BoundObj.begin(); it != mc_BoundObj.end(); it++)
			{

				string name(it->first);
				if (name.compare(desName) == 0)
				{
					it->second.socket->send(rawData, MSG_MAX_BUFFER_SIZE);

					//wait for recv msg back form client

					it->second.socket->recv(sendBack, MSG_MAX_BUFFER_SIZE);
					if (!isSendBackGood(std::string(sendBack)))
						shutDown();

					if(validMsg(std::string(sendBack)))
						sendTo = std::string(sendBack);
				}
			}

			recvSocket->send(MSG_CAN_SEND, MSG_MAX_BUFFER_SIZE);
		}
	}
}

bool Device::isSendBackGood(std::string sendBack)
{

	return !(sendBack.compare(MSG_SHUT_DOWN) == 0);
}

void Device::shutDown()
{

	std::unordered_map<std::string, BoundObject>::iterator it = mc_BoundObj.begin();
	for (; it != mc_BoundObj.end(); it++)
	{
		it->second.socket->send(MSG_SHUT_DOWN, MSG_MAX_BUFFER_SIZE);
	}
}

Device::~Device()
{
	bool running = m_Running.load(std::memory_order_seq_cst);
	if(running)
		Stop();

	std::unordered_map<std::string, BoundObject>::iterator it = mc_BoundObj.begin();
	for (; it != mc_BoundObj.end(); it++)
	{
	
		it->second.socket->cleanUp();
		delete it->second.socket;
	}
	s_LocalTCP_Socket->cleanUp();
	delete s_LocalTCP_Socket;
}

