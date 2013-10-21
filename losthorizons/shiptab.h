#ifndef _SHIPTAB_H_
#define _SHIPTAB_H_

#include "menutab.h"
#include "player.h"

class ShipTab : public MenuTab
{
public:
	ShipTab(IGUITabControl *tabs, Player* player);
	~ShipTab();

	void run();

private:
	Player* player;

	IGUIStaticText* shipName;
	IGUIStaticText* description;
	IGUIListBox* systemsList;
	IGUIStaticText* crewRq;
	IGUIStaticText* crewAv;
	IGUIStaticText* systemsHealth;
	IGUIButton* repair;
	IGUIButton* replace;
	void textUpdate();
};
#endif
