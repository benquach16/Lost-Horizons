#ifndef _HUD_H_
#define _HUD_H_

#include "stdafx.h"
#include "ship.h"

using namespace irr;

class HUD
{
public:
	HUD();
	//So this needs a bunch of inputs, mainly player information and the
	//player target information
	void run(const Ship *player);
	void setVisible(bool visible);
	virtual ~HUD();

private:
	void updatePlayerInfo(const ShipInformation &info);
	void updateTargetInfo(const Ship *player, const TargetableObject *target);

	//we're going to have this be the parent of everything in the hud
	//gui::IGUIElement *window;
	//the pointer to the background image for showing all the ship information
	gui::IGUIImage *shipWheel;

	gui::IGUIStaticText *velocity;
	gui::IGUIStaticText *hull;
	gui::IGUIStaticText *armor;
	gui::IGUIStaticText *shield;

	gui::IGUIImage *targetBkg;
	gui::IGUIStaticText *targetName;
	gui::IGUIStaticText *targetFaction;
	gui::IGUIStaticText *targetDistance;
	gui::IGUIStaticText *targetHull;
	gui::IGUIStaticText *targetArmor;
	gui::IGUIStaticText *targetShield;
};

#endif
