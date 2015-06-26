#ifndef _DEVCONSOLE_H_
#define _DEVCONSOLE_H_

//a simple command console

//#include <queue>
#include <forward_list>
#include <vector>

using namespace irr;

class DevConsole
{
public:
	DevConsole();
	~DevConsole();
	//take care of the first thing in the queue
	void run();
	
	//run a loop that allows you to add messages to the queue
	//void postMessage();

	void setVisible(bool show);
	bool getVisible() const;

	enum LOG_TYPE
	{
		LOG_STATUS,
		LOG_WARNING,
		LOG_ERROR,
		LOG_FATAL,
		LOG_COMMAND
	};

	void logPrint(const std::string& text); //log a regular message
	void logWarn(const std::string& text); //log a warning
	void logError(const std::string& text); //log an error
	void logFatal(const std::string& text); //log a fatal error and dump the report

	bool execute(const std::string& filename);

private:
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

	typedef bool (*function)(std::vector<std::string>& args);
	void registerCommand(const std::string& name, const function& command);
	bool executeCommand(const std::string& name, std::vector<std::string>& args);

	bool parse(std::string line = "");

	//std::queue<message> messages; going to just do shit immediately now
	std::forward_list< std::pair<std::string, function> > commands;
	char *buffer;
	unsigned size, index;
	bool error;
	unsigned errorEnd;
	std::vector<std::string> history;
	unsigned historyIndex;
	int scrollPosition;
	bool visible;

	std::vector< std::pair<std::string, LOG_TYPE> > log;
	gui::IGUIFont *font;
};

#endif
