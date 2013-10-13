#ifndef _GAMEMENU_H_
#define _GAMEMENU_H_

#include "menuwindow.h"
#include "player.h"
#include "shiptab.h"
#include "cargotab.h"
#include "missiontab.h"
//show ingame information in this menu

class GameMenu : public MenuWindow
{
public:
	GameMenu(Player* player, MissionManager *missionManager);
	~GameMenu();

	virtual void run();

protected:
	void initializeDisplay();
	
	Player* player;
	MissionManager *missionManager;

	gui::IGUITabControl* tabs;
	ShipTab* ship;
	CargoTab* cargo;
	//MenuTab* crew;
	//MenuTab* loadout;
	//MenuTab* hangar;
	MissionTab *mission;
};
#endif
