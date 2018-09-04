/*
 * SendBackContainer.h
 *
 *  Created on: Aug 28, 2018
 *      Author: thor
 */

#ifndef HEADER_SENDBACKCONTAINER_H_
#define HEADER_SENDBACKCONTAINER_H_

#include <deque>
#include <mutex>
#include <sys/time.h>

namespace uiRobotics {


struct SBCPair
{
	void* prt;
	char* msg;
};

class SendBackContainer {
public:

	typedef std::deque<SBCPair>::iterator iterator

	SendBackContainer(size_t size);
	virtual ~SendBackContainer();
	void add(char* msg);
	void addSub(char* subMessage);


protected:
	std::deque<SBCPair>* m_dque;
	size_t m_size;
	size_t m_current;

private:
	static long long getTimeStamp (void);
	static bool compareTimeStamp(long long left, long long right, long long interval);
	iterator where(void);
	size_t at;
	std::mutex* ms_mutex;
	iterator m_iterator;
}
};

}; /* namespace uiRobotics */

#endif /* HEADER_SENDBACKCONTAINER_H_ */
