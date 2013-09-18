#ifndef _SHIPTAB_H_
#define _SHIPTAB_H_

#include "menutab.h"

class ShipTab : public MenuTab
{
public:
	ShipTab(gui::IGUITabControl *tabs, Player* player);
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
	void textUpdate();
};
#endif
