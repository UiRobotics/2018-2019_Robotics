#include "../header/motor.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUF_MAX 256   // default max buffer size
#define TIMEOUT 5000 // default timeout
#define DEBUG 0

motor::motor(const char* port, int baud_rate=115200) : uiRobotics::BindableObj("motor_controller")
{
	fd=-1;
	fd = serialport_init(port, baud_rate); //opening port
    (fd == -1) ? std::cout<< "couldn't open port for arduino! :(" << std::endl : std::cout<< "opened port " << port << std::endl;
    serialport_flush(fd);
}

std::string motor::HandleGetMsg(void* msg)
{

	//std::string msgnew((char*)msg);
	//std::string message = ToArduinoFormat(msgnew);
   //std::cout<<"writing: "<<message<<std::endl;
   //const char* ard_message =message.c_str();

   int rd = serialport_write(fd, bullcrap.c_str());
   if(rd == -1) std::cout<<"error writing messages to arduino!" <<std::endl;
  // sleep(3);

/*#if DEBUG //if we are debugging let's get the messages back
   	char eolchar = '\n';
   	char* buf=(char*)malloc(BUF_MAX*sizeof(char));
	  memset(buf,0,BUF_MAX); //clearing buffer
    serialport_read_until(fd, buf, eolchar, BUF_MAX, TIMEOUT); //'Arduino received <message>'
    std::cout<<"Arduino Echoed: "<<buf<<std::endl;
    free(buf);
#endif*/

    return MSG_CAN_SEND;
}

std::string motor::ToArduinoFormat(std::string msg)
{

	std::string arduinoFormat;

	arduinoFormat.push_back('!');
	std::string command = msgParser::FindCommand(msg);

	if(command.compare("move_forward") == 0)
	{
		arduinoFormat.push_back(Mode::MOVE_FORWARD);
	}
	else if(command.compare("move_back") == 0)
	{
		arduinoFormat.push_back(Mode::MOVE_REVERSE);
	}
	else if(command.compare("turn_left") == 0)
	{
		arduinoFormat.push_back(Mode::TURN_LEFT);
	}
	else if(command.compare("turn_right") == 0)
	{
		arduinoFormat.push_back(Mode::TURN_RIGHT);
	}

	arduinoFormat.push_back('0');

	std::string val = msgParser::FindVal(msg);
	arduinoFormat.append(val);

	return arduinoFormat;
}
