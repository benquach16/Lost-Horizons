#include "stdafx.h"
#include "devconsole.h"
#include "globals.h"
#include "string_util.h"
//#include <conio.h>//stop using this once the devconsole becomes a menu
#include <sstream>
#include <fstream>

using namespace base;

namespace command
{
	//commands for the dev console are forward declared here and defined at the end of this file
	bool execute(std::vector<std::string>& args);
	bool create(std::vector<std::string>& args);
}

#define CONSOLEBUFFERSIZE 50

DevConsole::DevConsole()
	: //MenuWindow(guienv->addWindow(rect<s32>(0,0,width,height))),
	  //history(guienv->addListBox(rect<s32>(width/2-512,20,width/2+512,height-40), window)),
	  //editBox(guienv->addEditBox(L"this is the edit box!", rect<s32>(width/2-512,height-30,width/2+512,height-10), false, window)),
	  buf(new char[CONSOLEBUFFERSIZE+1]), size(0), index(0), historyIndex(0),
	  visible(false), font(guienv->getFont("res/font/aldo.xml"))
{
	//window->setDrawBackground(false);
	//window->setDraggable(false);
	//window->getCloseButton()->setVisible(false);
	//history->setAutoScrollEnabled(true);
	//editBox->setDrawBackground(false);
	//editBox->setMax(CONSOLEBUFFERSIZE);
	//editBox->setMultiLine(false);

	registerCommand("execute", command::execute);
	registerCommand("create", command::create);
	
	//hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//buf[0] = '\0';
	// for testing
	//strcpy_s(buf, CONSOLEBUFFERSIZE, "The console is now open! This is a test. let us see how many");
	//for (unsigned i = 0; i < 30; ++i) {
	//	history->addItem(L"This is the list box!");
	//}
}

DevConsole::~DevConsole()
{
	delete buf;
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
	/*
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
	*/

	//begin rewrite
	// check keys
	// should i just iterate through all keys and do case statement just like above?
	// or should i only check specific ones?

	///*
	//version 1 begin
	if (receiver->isKeyPressed(KEY_BACK) && index > 0) {
		index--;
		size--;
		for (unsigned i = index; i < size; ++i) {
			buf[i] = buf[i + 1];
		}
	}
	if (receiver->isKeyPressed(KEY_RETURN) && index > 0) {
		if (parse()) {
			//history.push_back(buf);
			//historyIndex = history.size();
			index = size = 0;
		}
	}
	if (receiver->isKeyPressed(KEY_SPACE) && size < CONSOLEBUFFERSIZE) {
		if (index < size) {
			for (unsigned i = size; i > index; --i) {
				buf[i] = buf[i - 1];
			}
		}
		buf[index] = ' ';
		index++;
		size++;
	}
	if (receiver->isKeyPressed(KEY_LEFT) && index > 0) {
		index--;
	}
	if (receiver->isKeyPressed(KEY_RIGHT) && index < size) {
		index++;
	}
	for (unsigned c = '0'; c < '9'; ++c) {
		if (receiver->isKeyPressed((EKEY_CODE)c) && size < CONSOLEBUFFERSIZE) {
			if (index < size) {
				for (unsigned i = size; i > index; --i) {
					buf[i] = buf[i - 1];
				}
			}
			buf[index] = tolower(c);
			index++;
			size++;
		}
	}
	for (unsigned c = 'A'; c < 'Z'; ++c) {
		if (receiver->isKeyPressed((EKEY_CODE)c) && size < CONSOLEBUFFERSIZE) {
			if (index < size) {
				for (unsigned i = size; i > index; --i) {
					buf[i] = buf[i - 1];
				}
			}
			buf[index] = tolower(c);
			index++;
			size++;
		}
	}
	if (receiver->isKeyDown(KEY_LCONTROL) && receiver->isKeyPressed(KEY_KEY_K)) {
		//historyIndex = history.size();
		if (index == size) {
			index = size = 0;
		} else {
			size = index;
		}
	}
	//version 1 end
	//*/
	//separation between versions
	/*
	//version 2 begin

	//version 2 end
	*/

	// draw shit
	vdriver->draw2DRectangle(video::SColor(50,0,50,150), rect<s32>(0,0,base::width,base::height));
	font->draw(L"The console is now open! This is a test. let's see how many characters can fill the spacea\nlalalaalalalalala hahahaahaha!~", rect<s32>(0,0,base::width,base::height), video::SColor(255,255,255,255));
	for (unsigned i = 0; i < 5; ++i) {
		vdriver->draw2DLine(vector2d<s32>(15,base::height-35),vector2d<s32>(25-i,base::height-25),video::SColor(255,0,150,50));
		vdriver->draw2DLine(vector2d<s32>(15,base::height-15),vector2d<s32>(25-i,base::height-25),video::SColor(255,0,150,50));
	}
	buf[size] = '\0';
	font->draw(buf, rect<s32>(30,base::height-40,base::width,base::height), video::SColor(255,0,150,50));
	
	// print buf size and index for testing
	font->draw(core::stringw(size), rect<s32>(80,80,base::width,base::height), video::SColor(255,255,255,255));
	font->draw(core::stringw(index), rect<s32>(110,90,base::width,base::height), video::SColor(255,255,255,255));
}

void DevConsole::setVisible(bool show)
{
	visible = show;
}

bool DevConsole::getVisible()
{
	return visible;
}

bool DevConsole::execute(const std::string filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		return false;
	}
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(file, line)) {
		if (!line.empty() && line[0] != '#') {
			lines.push_back(line);
		}
	}
	file.close();
	for (unsigned i = 0; i < lines.size(); ++i) {
		parse(lines[i]);
	}
	return true;
}

void DevConsole::registerCommand(const std::string& name, const function& command)
{
	commands.push_front(std::pair<std::string, function>(name, command));
}

bool DevConsole::executeCommand(const std::string& name, std::vector<std::string>& args)
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

bool DevConsole::parse(std::string line)
{
	std::stringstream tokenize;
	std::string command, token;
	std::vector<std::string> args;

	if (line.empty()) {
		buf[size] = '\0';
		tokenize << buf;
	} else {
		tokenize << line;
	}

	tokenize >> command;
	while (tokenize >> token) {
		args.push_back(token);
	}

	return executeCommand(command, args);
}


//definitions for dev console commands start here
bool command::execute(std::vector<std::string>& args)
{
	bool success = !args.empty();
	for (unsigned i = 0; i < args.size(); ++i) {
		success = success && console->execute(args[i]);
	}
	return success;
}

bool command::create(std::vector<std::string>& args)
{
	//make some needed variables with default values
	E_GAME_FACTION faction = (E_GAME_FACTION)0;
	f64 posX = 0, posY = 0, posZ = 0;

	//process the common stuff in the arguments
	for (unsigned i = 1; i < args.size(); ++i) {
		if (args[i] == "-abs") {
			args[i].clear();
			i++;
			if (!TryParse(args[i], &posX)) {
				return false;
			}
			args[i].clear();
			i++;
			if (!TryParse(args[i], &posY)) {
				return false;
			}
			args[i].clear();
			i++;
			if (!TryParse(args[i], &posZ)) {
				return false;
			}
			args[i].clear();
		} else if (args[i] == "-rel") {
			args[i].clear();
			i++;

			args[i].clear();
			// TODO
		} else if (args[i] == "-aim") {
			args[i].clear();
			i++;

			args[i].clear();
			// TODO
		} else if (args[i] == "-faction") {
			args[i].clear();
			i++;
			unsigned temp;
			if (!TryParse(args[i], &temp)) {
				return false;
			}
			faction = (E_GAME_FACTION)(temp%4);//add FACTION_COUNT to faction enums
			args[i].clear();
		}
	}

	//take care of the rest
	if (args.empty()) {
		return false;
	} else if (args[0] == "cam") {
		for (unsigned i = 1; i < args.size(); ++i) {
			if (!args[i].empty()) {
				return false;
			}
		}
		game->getGameSceneManager()->createPlayerCam(vector3df((f32)posX, (f32)posY, (f32)posZ));
	} else if (args[0] == "ship") {
		ObjectManager::E_SHIP_LIST shipType = (ObjectManager::E_SHIP_LIST)0;
		for (unsigned i = 1; i < args.size(); ++i) {
			if (args[i] == "-type") {
				args[i].clear();
				i++;
				unsigned temp;
				if (!TryParse(args[i], &temp)) {
					return false;
				}
				shipType = (ObjectManager::E_SHIP_LIST)(temp%3);//add SHIP_COUNT to ship enums
				args[i].clear();
			} else if (!args[i].empty()) {
				return false;
			}
		}
		game->getGameSceneManager()->createShip(faction, shipType, vector3df((f32)posX, (f32)posY, (f32)posZ));
	} else if (args[0] == "station") {
		ObjectManager::E_STATION_LIST stationType = (ObjectManager::E_STATION_LIST)0;
		for (unsigned i = 1; i < args.size(); ++i) {
			if (args[i] == "-type") {
				args[i].clear();
				i++;
				unsigned temp;
				if (!TryParse(args[i], &temp)) {
					return false;
				}
				stationType = (ObjectManager::E_STATION_LIST)(temp%2);//add STATION_COUNT to station enums
				args[i].clear();
			} else if (!args[i].empty()) {
				return false;
			}
		}
		game->getGameSceneManager()->createStation(faction, stationType, vector3df((f32)posX, (f32)posY, (f32)posZ));
	} else {
		return false;
	}

	return true;
}
