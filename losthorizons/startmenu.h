#ifndef _STARTMENU_H_
#define _STARTMENU_H_

#include "savemenu.h"
#include "optionmenu.h"
#include "messagemenu.h"
#include "datamanager.h"
#include "missionmenu.h"
using namespace irr;

//this is the start screen of the game
class StartMenu : public MenuWindow
{
public:
	StartMenu(DataManager *data);
	~StartMenu();

	void run(MissionMenu *missionMenu);
	void shift();

private:
	DataManager *data;
	bool saved;
	bool close;
	OptionMenu *config;
	MessageMenu *confirmClose;
	gui::IGUIButton *resume;
	gui::IGUIButton *newgame;
	gui::IGUIButton *loadgame;
	gui::IGUIButton *savegame;
	gui::IGUIButton *closegame;
	gui::IGUIButton *options;
	gui::IGUIButton *quit;
};
#endif
