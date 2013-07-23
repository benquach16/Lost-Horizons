#ifndef _HUD_H_
#define _HUD_H_

#include "irrlicht.h"

using namespace irr;
using namespace gui;

class HUD
{
public:
	HUD();
	~HUD();
private:
	//we're going to have this be the parent of everything in the hud
	IGUIWindow *base;
};

#endif
