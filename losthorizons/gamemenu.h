#ifndef _GAMEMENU_H_
#define _GAMEMENU_H_

#include "menuwindow.h"
#include "shiptab.h"
#include "cargotab.h"
#include "missiontab.h"
//show ingame information in this menu

class GameMenu : public MenuWindow
{
public:
	GameMenu(Ship *player);
	~GameMenu();
	virtual void run();

protected:
	gui::IGUITabControl* tabs;
	ShipTab* ship;
	CargoTab* cargo;
	MissionTab *mission;
	//CrewTab* crew;
	//LoadoutTab* loadout;
};
#endif
