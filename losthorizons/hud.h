#ifndef _HUD_H_
#define _HUD_H_

#include "irrlicht.h"
#include "object.h"
#include "menuwindow.h"

using namespace irr;
using namespace gui;

class HUD
{
public:
	HUD();
	//initialize all the cool pictures n shit here
	void initializeDisplay();
	//So this needs a bunch of inputs, mainly player information and the
	//player target information
	void run(Object *playerTarget);
	void setVisible(bool visible);
	virtual ~HUD();
private:
	//we're going to have this be the parent of everything in the hud
	gui::IGUIWindow *window;
	//the pointer to the background image for showing all the ship information
	gui::IGUIImage *shipWheel;
};

#endif
