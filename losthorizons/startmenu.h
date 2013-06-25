#ifndef _STARTMENU_H_
#define _STARTMENU_H_

#include "menuwindow.h"
#include "irrlicht.h"
#include "optionmenu.h"

using namespace irr;
using namespace core;
using namespace video;

//this is the start screen of the game
class StartMenu : public MenuWindow
{
public:
	StartMenu(irr::IrrlichtDevice *graphics);
	~StartMenu();

	bool run();

private:
	bool flip;
	OptionMenu *config;
	scene::ICameraSceneNode *cam;
	scene::ISceneNode *corona;
	scene::IParticleSystemSceneNode *nebula;
	scene::IAnimatedMeshSceneNode *asteroids;
	gui::IGUIImage *logo;
	gui::IGUIButton *resume;
	gui::IGUIButton *newgame;
	gui::IGUIButton *loadgame;
	gui::IGUIButton *savegame;
	gui::IGUIButton *closegame;
	gui::IGUIButton *options;
	gui::IGUIButton *quit;
};
#endif
