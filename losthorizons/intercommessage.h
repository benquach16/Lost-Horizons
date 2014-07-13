#ifndef _INTERCOMMESSAGE_H_
#define _INTERCOMMESSAGE_H_

#include <irrlicht.h>
#include <string>

//class that we're going to use ot eventually overhaul the intercom system
class IntercomMessage
{
public:
	IntercomMessage();
	~IntercomMessage();
	
	void run();
private:
	std::string sender;
	std::string message;

	unsigned int messageLifetime;
	
};

#endif
