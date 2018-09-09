/*
 * SendBackContainer.h
 *
 *  Created on: Aug 28, 2018
 *      Author: thor
 */

#ifndef HEADER_SENDBACKCONTAINER_H_
#define HEADER_SENDBACKCONTAINER_H_

#include <map>
#include <vector>
#include <mutex>
#include <sys/time.h>
#include <math.h>

namespace uiRobotics {

struct timeCompare{
	inline bool operator() (const long long& left, const long long& right)
	{
		return left<right;
	}
};


class SendBackContainer {
public:

	SendBackContainer(size_t size);
	virtual ~SendBackContainer();
	void add(char* msg);
	void addSub(char* subMessage);
	std::string getMessage();


protected:
	std::map<long long, std::string, timeCompare>* m_subMessages;
	std::map<long long, std::string, timeCompare>* m_comMessages;
private:
	static long long getTimeStamp (void);
	static bool compareTimeStamp(long long left, long long right, long long interval);
	std::mutex* ms_mutex;
	int m_numberOfIterations;
};

}; /* namespace uiRobotics */

#endif /* HEADER_SENDBACKCONTAINER_H_ */
