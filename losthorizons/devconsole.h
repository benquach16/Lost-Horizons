#ifndef _DEVCONSOLE_H_
#define _DEVCONSOLE_H_

//a simple command console

#include <queue>

class DevConsole
{
public:
	DevConsole();
	~DevConsole();
	//take care of the first thing in the queue
	void run();

private:
	enum E_ACTION_TYPE
	{
		ACTION_TOGGLE,
		ACTION_CREATE
	};

	struct message
	{
		E_ACTION_TYPE action;
		void *args;//int argc;char* argv[]; still need to figure out how this will be done
		void run();
	};

	std::queue<message*> messages;
};

#endif
