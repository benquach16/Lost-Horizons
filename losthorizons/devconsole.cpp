#include "stdafx.h"
#include "devconsole.h"
#include "globals.h"
#include "string_util.h"
#include <sstream>
#include <fstream>

using namespace base;

namespace command
{
	//commands for the dev console are forward declared here and defined at the end of this file
	bool execute(std::vector<std::string>& args);
	bool create(std::vector<std::string>& args);
	bool move(std::vector<std::string>& args);
}

const int CONSOLEBUFFERSIZE = 80;
const int HISTORYPOSITIONX = 40;
const int HISTORYPOSITIONY = 40;
const int SCROLLINCREMENT = 10;
const int EDITLINEPOSITIONX = 30;
const int EDITLINEPOSITIONY = 10;
const int CURSORBLINKTIME = 500;
const int ERRORTIME = 2000;
const int FONTWIDTH = 11;

DevConsole::DevConsole()
	: buffer(new char[CONSOLEBUFFERSIZE+1]), size(0), index(0),
	  error(false), errorEnd(0), historyIndex(0), scrollPosition(0),
	  visible(false), font(guienv->getFont("res/font/sans_mono.png"))
{
	registerCommand("execute", command::execute);
	registerCommand("create", command::create);
	registerCommand("move", command::move);


	//add junk to history for testing
	history.push_back("This is a command");
	history.push_back("This is another command");
	for (unsigned i = 0; i < 23; ++i) {
		history.push_back("test test test test test");
	}
	history.push_back("last command");
	historyIndex=history.size();
}

DevConsole::~DevConsole()
{
	delete buffer;
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
	// update
	EKEY_CODE keyPressed = receiver->getKey();
	switch (keyPressed)
	{
	case 0:
	case KEY_OEM_3:
		break;
	case KEY_LBUTTON:
		{
			const unsigned x = receiver->getMouseX()+3;
			const unsigned y = receiver->getMouseY()+5;
			if (y > EDITLINEPOSITIONY && y < EDITLINEPOSITIONY+30 &&
				x > EDITLINEPOSITIONX && x < EDITLINEPOSITIONX+FONTWIDTH*(size+1)) {
				index = (x - EDITLINEPOSITIONX)/FONTWIDTH;
			}
		}
		break;
	case KEY_RBUTTON:
		// context menu
		break;
	case KEY_BACK:
		if (index > 0) {
			index--;
			size--;
			for (unsigned i = index; i < size; ++i) {
				buffer[i] = buffer[i + 1];
			}
		}
		break;
	case KEY_TAB:
		// autocomplete shit
		break;
	case KEY_RETURN:
		if (size > 0) {
			scrollPosition = 0;
			if (parse()) {
				history.push_back(buffer);
				historyIndex = history.size();
				index = size = 0;
			} else {
				error = true;
				errorEnd = timer->getTime() + ERRORTIME;
			}
		}
		break;
	case KEY_END:
		index = size;
		break;
	case KEY_HOME:
		index = 0;
		break;
	case KEY_LEFT:
		if (index > 0) {
			index--;
		}
		break;
	case KEY_UP:
		if (historyIndex < history.size()) {
				historyIndex++;
			if (historyIndex < history.size()) {
				strcpy_s(buffer, CONSOLEBUFFERSIZE, history[historyIndex].c_str());
				index = size = history[historyIndex].size();
			} else {
				index = size = 0;
			}
		}
		break;
	case KEY_RIGHT:
		if (index < size) {
			index++;
		}
		break;
	case KEY_DOWN:
		if (historyIndex > 0) {
			historyIndex--;
			strcpy_s(buffer, CONSOLEBUFFERSIZE, history[historyIndex].c_str());
			index = size = history[historyIndex].size();
		}
		break;
	case KEY_DELETE:
		historyIndex = history.size();
		if (index == size) {
			index = size = 0;
		} else {
			size = index;
		}
		break;
	default:
		{
			char c = receiver->getChar();
			if (size < CONSOLEBUFFERSIZE && c >= ' ' && c < '~') {
				if (index < size) {
					for (unsigned i = size; i > index; --i) {
						buffer[i] = buffer[i - 1];
					}
				}
				buffer[index] = c;
				index++;
				size++;
			}
		}
		break;
	}
	if (history.size()*20 > height-EDITLINEPOSITIONY-HISTORYPOSITIONY) {
		scrollPosition -= receiver->getMouseWheel()*SCROLLINCREMENT;
		if (scrollPosition < 0) {
			scrollPosition = 0;
		} else if ((u32)scrollPosition > HISTORYPOSITIONY+EDITLINEPOSITIONY-height+history.size()*20) {
			scrollPosition = HISTORYPOSITIONY+EDITLINEPOSITIONY-height+history.size()*20;
		}
	}

	// draw
	vdriver->draw2DRectangle(video::SColor(50,0,50,150), rect<s32>(0,0,width,height));
	rect<s32> clip(0,HISTORYPOSITIONY,width,height-EDITLINEPOSITIONY);
	for (unsigned i = 0; i < history.size(); ++i) {
		font->draw(history[i].c_str(), rect<s32>(HISTORYPOSITIONX,HISTORYPOSITIONY-scrollPosition+(history.size()-1-i)*20,0,0), video::SColor(255,0,150,50), false, false, &clip);
	}
	buffer[size] = '\0';
	font->draw(buffer, rect<s32>(EDITLINEPOSITIONX,EDITLINEPOSITIONY,0,0), video::SColor(255,0,150,50));
	font->draw(">", rect<s32>(EDITLINEPOSITIONX-13,EDITLINEPOSITIONY,0,0), video::SColor(255,0,150,50));
	if (timer->getTime()/CURSORBLINKTIME%2 == 0) {
		font->draw("_", rect<s32>(EDITLINEPOSITIONX+FONTWIDTH*index,EDITLINEPOSITIONY+2,0,0), video::SColor(255,0,150,50));
	}
	if (error) {
		vdriver->draw2DLine(vector2d<s32>(EDITLINEPOSITIONX,EDITLINEPOSITIONY+20), vector2d<s32>(EDITLINEPOSITIONX+FONTWIDTH*size,EDITLINEPOSITIONY+20), video::SColor(150,255,0,0));
		if (timer->getTime() > errorEnd) {
			error = false;
		}
	}
}

void DevConsole::setVisible(bool show)
{
	visible = show;
}

bool DevConsole::getVisible() const
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
		buffer[size] = '\0';
		tokenize << buffer;
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

//this function is big and super ugly
//gotta rewrite stuff
//simplify this into multiple commands
//create, move, destroy
//other functions that will be needed: show IDs, godmode
bool command::create(std::vector<std::string>& args)
{
	//make some needed variables with default values
	E_GAME_FACTION faction = (E_GAME_FACTION)0;
	f64 posX = 0, posY = 0, posZ = 0;

	//process the common stuff in the arguments
	for (unsigned i = 1; i < args.size(); ++i) {
		if (args[i] == "-faction") {
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

bool command::move(std::vector<std::string>& args)
{
	if (TargetableObject::allTargets.empty()) {
		return true;
	}
	unsigned ID = TargetableObject::allTargets.back()->getID();
	vector3df pos;
	for (unsigned i = 0; i < args.size(); ++i) {
		if (args[i] == "id") {
			if (args.size() <= i+1 || !TryParse(args[i+1], &ID)) {
				return false;
			}
		} else if (args[i] == "absolute") {
			if (args.size() <= i+3 ||
				!TryParse(args[i+1], &pos.X) ||
				!TryParse(args[i+2], &pos.Y) ||
				!TryParse(args[i+3], &pos.Z)) {
				return false;
			}
		} else if (args[i] == "relative") {
			if (args.size() <= i+3 ||
				!TryParse(args[i+1], &pos.X) ||
				!TryParse(args[i+2], &pos.Y) ||
				!TryParse(args[i+3], &pos.Z)) {
				return false;
			}
			pos += vector3df(0);//should actually get the position
		} else if (args[i] == "distance") {
			f32 distance;
			if (args.size() <= i+1 || !TryParse(args[i+1], &distance)) {
				return false;
			}
			//calculate where the position should be
		}
	}
	unsigned i = 0;
	while (TargetableObject::allTargets[i]->getID() != ID) {
		i++;
	}
	TargetableObject::allTargets[i]->setPosition(pos);
	return true;
}
