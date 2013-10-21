#ifndef _CARGOTAB_H_
#define _CARGOTAB_H_

#include "menutab.h"
#include "player.h"

class CargoTab : public MenuTab
{
public:
	CargoTab(IGUITabControl *tabs, Player* player);
	~CargoTab();

	void run();

private:
	Player* player;

	IGUIListBox* itemList;
	IGUIStaticText* costTxtBox;
	IGUIStaticText* weightTxtBox;
	IGUIStaticText* descriptionTxtBox;

	void itemListUpdate();
	void showItemInfo();
};
#endif