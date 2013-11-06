#ifndef _CARGOTAB_H_
#define _CARGOTAB_H_

#include "menutab.h"
#include "inventory.h"

class CargoTab : public MenuTab
{
public:
	CargoTab(IGUITabControl *tabs, Inventory &playerData);
	~CargoTab();

	void run();

private:
	IGUIListBox* itemList;
	IGUIStaticText* costTxtBox;
	IGUIStaticText* weightTxtBox;
	IGUIStaticText* descriptionTxtBox;

	void itemListUpdate();
	void showItemInfo();

	Inventory &playerData;
};

#endif
