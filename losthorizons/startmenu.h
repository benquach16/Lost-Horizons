#ifndef _STARTMENU_H_
#define _STARTMENU_H_

#include "menuwindow.h"
#include "savemenu.h"
#include "optionmenu.h"
#include "messagemenu.h"
#include "keylistener.h"

using namespace irr;
using namespace core;
using namespace video;

//this is the start screen of the game
class StartMenu : public MenuWindow
{
public:
	StartMenu(IrrlichtDevice *graphics, KeyListener *receiver);
	~StartMenu();

	void run();

private:
	void shift();

	IrrlichtDevice *graphics;
	KeyListener *receiver;
	bool exit;
	bool play;
	OptionMenu *config;
	MessageMenu *confirmQuit;
	gui::IGUIButton *resume;
	gui::IGUIButton *newgame;
	gui::IGUIButton *loadgame;
	gui::IGUIButton *savegame;
	gui::IGUIButton *closegame;
	gui::IGUIButton *options;
	gui::IGUIButton *quit;
};
#endif
