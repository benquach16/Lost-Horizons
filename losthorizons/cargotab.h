#ifndef _CARGOTAB_H_
#define _CARGOTAB_H_

#include "menutab.h"

class CargoTab : public MenuTab
{
public:
	CargoTab(gui::IGUITabControl *tabs, Player* player);
	~CargoTab();

	void run();
private:
	Player* player;

	IGUIListBox* heavyMetalList;
	IGUIListBox* costList;
	IGUIListBox* weightList;
	IGUIListBox* descriptionList;
};
#endif