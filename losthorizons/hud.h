#ifndef _HUD_H_
#define _HUD_H_

#include "irrlicht.h"
#include "object.h"
#include "menuwindow.h"
#include "player.h"

using namespace irr;
using namespace gui;

class HUD
{
public:
	HUD(Player *player);
	//initialize all the cool pictures n shit here
	void initializeDisplay();
	//So this needs a bunch of inputs, mainly player information and the
	//player target information
	void run();
	void setVisible(bool visible);
	virtual ~HUD();
private:
	void updatePlayerInfo();
	void updateTargetInfo();

	const wchar_t *getFactionName(E_GAME_FACTIONS faction);
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

	//pointer to tha player so we can grab information
	Player *player;
};

#endif
