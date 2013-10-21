#ifndef _STATIONMENU_H_
#define _STATIONMENU_H_

#include "player.h"
#include "spacestation.h"
#include "menuwindow.h"
#include "storetab.h"
#include "hangartab.h"

//ui menu that is opened when the player is docked at a space staiton
class StationMenu : public MenuWindow
{
public:
	StationMenu(Player *player);
	virtual ~StationMenu();
	void run(const TargetableObject *target);
	
protected:
	void initializeDisplay();

	gui::IGUITabControl *tabs;
	StoreTab *store;
	HangarTab *hangar;

	Player *player;
};

#endif
