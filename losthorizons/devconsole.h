#ifndef _DEVCONSOLE_H_
#define _DEVCONSOLE_H_

#define CONSOLEBUFFERSIZE 80

//a simple command console

#include <queue>
#include <list>

class DevConsole
{
public:
	DevConsole();
	~DevConsole();
	//take care of the first thing in the queue
	void run();
	//run a loop that allows you to add messages to the queue
	void postMessage();

private:
	enum KEY_PRESS
	{
		KB_RETURN = '\r',
		KB_GRAVEACCENT = '`',
		KB_BACKSPACE = '\b',
		KB_SPECIAL1 = 0,
		KB_SPECIAL2 = 0xE0,
		KB_UP = 72,
		KB_LEFT = 75,
		KB_RIGHT = 77,
		KB_DOWN = 80
	};

	enum E_ACTION_TYPE
	{
		ACTION_TOGGLE,
		ACTION_CREATE,
		ACTION_DESTROY
	};

	struct message
	{
		E_ACTION_TYPE action;
		void *args;//int argc;char* argv[]; still need to figure out how this will be done
		void run();
	};

	std::queue<message> messages;
	char buf[CONSOLEBUFFERSIZE];
	unsigned size, index;
	std::list<char*> history;

	HANDLE hstdout;
};

#endif
