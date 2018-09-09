/*
 * SendBackContainer.cpp
 *
 *  Created on: Aug 28, 2018
 *      Author: thor
 */

#include "../header/SendBackContainer.h"

namespace uiRobotics {

SendBackContainer::SendBackContainer(size_t size)
	:m_numberOfIterations(0)
{
	m_subMessages = new std::map<long long, std::string, timeCompare>();
	m_comMessages = new std::map<long long, std::string, timeCompare>();

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

	long long dif = abs(right - left);



	if (dif < interval)
	{
		return true;
	}
	else
	{
		return false;
	}

}

std::string SendBackContainer::getMessage(){
	long long currentTime = getTimeStamp();
	long remainder = (long)currentTime % 1000;
	long dividedRemainder = remainder / 100;

	std::string val;

	ms_mutex->lock();
	if(dividedRemainder > (long)m_numberOfIterations){

		std::map<long long, std::string, timeCompare>::iterator iter = m_comMessages->upper_bound(0);

		val = iter->second;
	}
	else{

		std::map<long long, std::string, timeCompare>::iterator iter = m_subMessages->upper_bound(0);

		val = iter->second;
	}

	ms_mutex->unlock();
	return val;
}

void SendBackContainer::add(char* msg)
{
	ms_mutex->lock();
	m_comMessages->emplace(getTimeStamp(), std::string(msg));

	ms_mutex->unlock();
}

void SendBackContainer::addSub(char* subMessage){
	ms_mutex->lock();
	m_subMessages->emplace(getTimeStamp(), std::string(subMessage));

	ms_mutex->unlock();
}


SendBackContainer::~SendBackContainer()
{
	delete(m_comMessages);
	delete(m_subMessages);
	delete(ms_mutex);
}

}
/* namespace uiRobotics */
