#ifndef _INTERCOMHANDLER_H_
#define _INTERCOMHANDLER_H_

#include "intercommessage.h"
#include <vector>

class IntercomHandler
{
public:
	IntercomHandler();
	~IntercomHandler();

	void run();
private:
	std::vector<IntercomMessage> messages;
};

#endif
