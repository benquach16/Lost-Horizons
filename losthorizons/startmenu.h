#ifndef _STARTMENU_H_
#define _STARTMENU_H_

#include "menuwindow.h"
#include "savemenu.h"
#include "optionmenu.h"
#include "messagemenu.h"
#include "datamanager.h"

using namespace irr;

//this is the start screen of the game
class StartMenu : public MenuWindow
{
public:
	StartMenu(DataManager *data);
	~StartMenu();

	void run();
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
