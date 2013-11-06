#ifndef _SHIPTAB_H_
#define _SHIPTAB_H_

#include "menutab.h"
#include "ship.h"

class ShipTab : public MenuTab
{
public:
	ShipTab(IGUITabControl *tabs, Ship* player);
	~ShipTab();

	void run();

private:
	IGUIStaticText* shipName;
	IGUIStaticText* description;
	IGUIListBox* systemsList;
	IGUIStaticText* crewRq;
	IGUIStaticText* crewAv;
	IGUIStaticText* systemsHealth;
	IGUIButton* repair;
	IGUIButton* replace;
	void textUpdate();

	Ship* player;
};
#endif
