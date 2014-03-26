#ifndef _DEVCONSOLE_H_
#define _DEVCONSOLE_H_

#define CONSOLEBUFFERSIZE 80

//a simple command console

//#include <queue>
#include <forward_list>
#include <vector>

class DevConsole
{
public:
	DevConsole();
	~DevConsole();
	//take care of the first thing in the queue
	void run();
	//run a loop that allows you to add messages to the queue
	//void postMessage();

private:
	enum KEY_PRESS
	{
		KB_RETURN = '\r',
		KB_GRAVEACCENT = '`',
		KB_TAB = '\t',
		KB_BACKSPACE = '\b',
		KB_CONTROL_K = 11,
		KB_SPECIAL1 = 0,
		KB_SPECIAL2 = 0xE0,
		// AFTER KB_SPECIAL2
		KB_HOME = 71,
		KB_END = 79,
		KB_UP = 72,
		KB_LEFT = 75,
		KB_RIGHT = 77,
		KB_DOWN = 80
	};

	/*enum E_ACTION_TYPE
	{
		ACTION_TOGGLE,
		ACTION_CREATE,
		ACTION_DESTROY
	};*/

	//struct message
	//{
	//	E_ACTION_TYPE action;
	//	void *args;//int argc;char* argv[]; still need to figure out how this will be done
	//	void run();
	//};

	typedef bool (*function)(const void* args);
	void registerCommand(const std::string& name, const function& command);
	bool executeCommand(const std::string& name, void* args);

	void clearLine();
	bool parse();

	//std::queue<message> messages; going to just do shit immediately now
	char buf[CONSOLEBUFFERSIZE];
	unsigned size, index;
	std::forward_list< std::pair<std::string, function> > commands;
	std::vector<std::string> history;
	unsigned historyIndex;

	HANDLE hstdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
};

#endif
