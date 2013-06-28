#ifndef _STARTMENU_H_
#define _STARTMENU_H_

#include "menuwindow.h"
#include "optionmenu.h"
#include "messagemenu.h"

using namespace irr;
using namespace core;
using namespace video;

//this is the start screen of the game
class StartMenu : public MenuWindow
{
public:
	StartMenu();
	~StartMenu();

	bool run();

private:
	bool flip;
	OptionMenu *config;
	MessageMenu *confirmQuit;
	scene::ISceneNode *corona;
	scene::IParticleSystemSceneNode *nebula;
	scene::IAnimatedMeshSceneNode *asteroids;
	gui::IGUIButton *resume;
	gui::IGUIButton *newgame;
	gui::IGUIButton *loadgame;
	gui::IGUIButton *savegame;
	gui::IGUIButton *closegame;
	gui::IGUIButton *options;
	gui::IGUIButton *quit;
};
#endif
