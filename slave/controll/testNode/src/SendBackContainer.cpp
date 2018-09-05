/*
 * SendBackContainer.cpp
 *
 *  Created on: Aug 28, 2018
 *      Author: thor
 */

#include "../header/SendBackContainer.h"

namespace uiRobotics {

SendBackContainer::SendBackContainer(size_t size)
	: m_current(0x0000)
	, m_iterator()
{
	m_size = size;
	m_dque = new std::deque<SBCPair>(size);
	ms_mutex = new std::mutex();

}

long long SendBackContainer::getTimeStamp()
{

	struct timeval tp;
	gettimeofday(&tp, NULL);
	long long mslong = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000;

	return mslong;
}

bool SendBackContainer::compareTimeStamp(long long left, long long right, long long interval){

	long long dif = right - left;

	if (dif < interval)
	{
		return true;
	}
	else
	{
		return false;
	}

}

char* SendBackContainer::getMessage(){
	long long myTimeStamp = getTimeStamp();

	ms_mutex->lock();
	if(compareTimeStamp())
`	{

	}
	ms_mutex->unlock();
}

void SendBackContainer::add(char* msg)
{
	ms_mutex->lock();
	SBCPair pair;
	pair.msg = msg;
	pair.prt = new std::vector();

	m_dque->push_back(pair);

	ms_mutex->unlock();
}

void SendBackContainer::addSub(char* subMessage){

	char* copyMessage = malloc(sizeof(char)*(strlen(subMessage)+1));

	memcpy(copyMessage, subMessage, strlen(subMessage)+1);


	ms_mutex->lock();
	m_dque->operator[](m_at).prt->push_back(copyMessage);
	ms_mutex->unlock();
}

iterator SendBackContainer::where(){
	return m_dque->begin()+at;
}

SendBackContainer::~SendBackContainer()
{
	delete(m_dque);
	delete(ms_mutex);
}

} /* namespace uiRobotics */
