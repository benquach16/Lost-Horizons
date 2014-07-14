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
	void initializePlayerShipsInFleet(const Fleet *playerFleet);
	void updatePlayerShipsInFleet(const Fleet *playerFleet);

	void setFleetVisible(bool visibile);
	virtual ~HUD();

	//use a struct for ui handling
	struct fleetShipInfo
	{
		gui::IGUIImage *bkgImage;
		gui::IGUIStaticText *name;
		gui::IGUIStaticText *hull;
		gui::IGUIStaticText *armor;
		gui::IGUIStaticText *shield;
		gui::IGUIStaticText *currentOrder;
	};

private:
	void updatePlayerInfo(const ShipInformation &info);
	void updateTargetInfo(const Ship *player, const TargetableObject *target);
	void clearPlayerFleetList();
	//we're going to have this be the parent of everything in the hud
	//gui::IGUIElement *window;
	//the pointer to the background image for showing all the ship information
	gui::IGUIImage *shipWheel;

	gui::IGUIStaticText *velocity;
	gui::IGUIStaticText *hull;
	gui::IGUIStaticText *armor;
	gui::IGUIStaticText *shield;
	gui::IGUIStaticText *energy;

	gui::IGUIImage *targetBkg;
	gui::IGUIStaticText *targetName;
	gui::IGUIStaticText *targetFaction;
	gui::IGUIStaticText *targetDistance;
	gui::IGUIStaticText *targetHull;
	gui::IGUIStaticText *targetArmor;
	gui::IGUIStaticText *targetShield;

	gui::IGUIStaticText *playerMode;

	std::vector<fleetShipInfo> playerShipsInFleet;
};

#endif
