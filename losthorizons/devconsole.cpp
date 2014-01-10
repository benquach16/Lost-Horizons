#include "stdafx.h"
#include "devconsole.h"
#include "globals.h"
#include <conio.h>
#include <sstream>

using namespace base;

bool create(const std::stringstream& tokenize);

DevConsole::DevConsole()
	: size(0), index(0), historyIndex(0)
{
	registerCommand("create", create);

	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	buf[0] = '\0';
}

DevConsole::~DevConsole()
{
}

//void DevConsole::run()
//{
//	if (!messages.empty()) {
//		//messages.front().run();
//		messages.pop();
//	}
//}

void DevConsole::run()
{
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	COORD returnPos = csbi.dwCursorPosition;

	_putch('\n');
	_cputs(buf);

	int keyPressed;
	do {
		keyPressed = _getch();
		switch (keyPressed) {
		case KB_RETURN:
			if (parse()) {
				clearLine();
				SetConsoleCursorPosition(hstdout, returnPos);
				returnPos.Y++;
				_putch('>');
				_cputs(buf);
				_cputs("\n\n");
				history.push_back(buf);
				historyIndex = history.size();
				index = size = 0;
				token.clear();
			}
			break;
		case KB_GRAVEACCENT:
			buf[size] = '\0';
			if (size > 0) {
				clearLine();
				index = size;
			}
			SetConsoleCursorPosition(hstdout, returnPos);
			break;
		case KB_TAB:
			// autocomplete stuff
			break;
		case KB_BACKSPACE:
			if (index > 0) {
				index--;
				size--;
				_putch('\b');
				if (index == size) {
					_cputs(" \b");
				} else {
					GetConsoleScreenBufferInfo(hstdout, &csbi);
					for (unsigned i = index; i < size; ++i) {
						buf[i] = buf[i + 1];
						_putch(buf[i]);
					}
					_putch(' ');
					SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
				}
			}
			break;
		case KB_CONTROL_K:
			historyIndex = history.size();
			if (index == size) {
				clearLine();
				index = size = 0;
			} else {
				GetConsoleScreenBufferInfo(hstdout, &csbi);
				for (unsigned i = index; i < size; ++i) {
					_putch(' ');
				}
				size = index;
				SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
			}
			break;
		case KB_SPECIAL1:
			_getch();
			break;
		case KB_SPECIAL2:
			switch (_getch()) {
			case KB_HOME:
				GetConsoleScreenBufferInfo(hstdout, &csbi);
				index = csbi.dwCursorPosition.X = 0;
				SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
				break;
			case KB_END:
				GetConsoleScreenBufferInfo(hstdout, &csbi);
				index = csbi.dwCursorPosition.X = size;
				SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
				break;
			case KB_UP:
				if (historyIndex > 0) {
					historyIndex--;
					clearLine();
					_cputs(history[historyIndex].c_str());
					memcpy(buf, history[historyIndex].c_str(), history[historyIndex].size());
					index = size = history[historyIndex].size();
				}
				break;
			case KB_LEFT:
				if (index > 0) {
					GetConsoleScreenBufferInfo(hstdout, &csbi);
					csbi.dwCursorPosition.X--;
					SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
					index--;
				}
				break;
			case KB_RIGHT:
				if (index < size) {
					GetConsoleScreenBufferInfo(hstdout, &csbi);
					csbi.dwCursorPosition.X++;
					SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
					index++;
				}
				break;
			case KB_DOWN:
				if (historyIndex < history.size() - 1) {
					historyIndex++;
					clearLine();
					_cputs(history[historyIndex].c_str());
					memcpy(buf, history[historyIndex].c_str(), history[historyIndex].size());
					index = size = history[historyIndex].size();
				}
				break;
			}
			break;
		default:
			if (size < CONSOLEBUFFERSIZE - 1 && __isascii(keyPressed)) {
				_putch(keyPressed);
				if (index < size) {
					GetConsoleScreenBufferInfo(hstdout, &csbi);
					for (unsigned i = index; i < size; ++i) {
						_putch(buf[i]);
					}
					for (unsigned i = size; i > index; --i) {
						buf[i] = buf[i - 1];
					}
					SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
				}
				buf[index] = keyPressed;
				index++;
				size++;
			}
			break;
		}
	} while (keyPressed != KB_GRAVEACCENT);
}

void DevConsole::registerCommand(const std::string& name, const function& command)
{
	commands.push_front(std::pair<std::string, function>(name, command));
}

bool DevConsole::executeCommand(const std::string& name, const std::stringstream& args)
{
	std::forward_list< std::pair<std::string, function> >::iterator i = commands.begin();
	while (i != commands.end()) {
		if ((*i).first == name) {
			return (*i).second(args);
		}
		i++;
	}
	return false;
}

void DevConsole::clearLine()
{
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	csbi.dwCursorPosition.X = 0;
	SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
	for (unsigned i = 0; i < size; ++i) {
		_putch(' ');
	}
	SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
}

bool DevConsole::parse()
{
	// make sure it's valid here
	// now figure out what it does and add it to the queue
	buf[size] = '\0';
	std::stringstream tokenize;
	tokenize << buf;
	tokenize >> token;
	return executeCommand(token, tokenize);
}

bool create(const std::stringstream& tokenize)
{
	//do shit

	return true;
}
