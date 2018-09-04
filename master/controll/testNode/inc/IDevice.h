/*
 * IDevice.h
 *
 *  Created on: Jan 26, 2017
 *      Author: Joseph
 */

#ifndef IDEVICE_H_
#define IDEVICE_H_

#include "BindableObj.h"

namespace uiRobotics
{

	class IDevice
	{
	public:

		virtual void Release(void){};
		virtual void Start(void){};
		virtual void Bind(BindableObj* obj){};
		virtual void SetServerPort(unsigned short port){};
		virtual void Stop(void){};
	protected:
		~IDevice(void){}
		IDevice(void){}
	};

	void CREATE_UI_ROBOTICS_DEVICE(IDevice** dev, char* localPort);

	class exception : public std::exception
	{
	public:
		exception(std::string what);

		virtual std::string what();

		virtual ~exception();
	private:
		std::string m_What;
	};

}

#endif /* IDEVICE_H_ */
