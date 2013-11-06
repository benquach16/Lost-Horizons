#ifndef _HANGARTAB_H_
#define _HANGARTAB_H_

#include "menutab.h"
#include "ship.h"

//class for the station refit menu
class HangarTab : public MenuTab
{
public:
	HangarTab(IGUITabControl *tabs, Ship *player);
	~HangarTab();
	virtual void run();

private:
	void loadInventories();
	void loadWeaponLists();
	void refitWeapons();

	IGUIComboBox *heavySlot;
	IGUIComboBox *heavySlotWeapon;

	IGUIComboBox *mediumSlot;
	IGUIComboBox *mediumSlotWeapon;

	IGUIComboBox *lightSlot;
	IGUIComboBox *lightSlotWeapon;

	IGUIButton *refit;
	IGUIButton *repair;

	int currentSelection[4];

	Ship *player;
};

#endif
