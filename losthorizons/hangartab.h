#ifndef _HANGARTAB_H_
#define _HANGARTAB_H_

#include "menutab.h"
#include "player.h"
#include "spacestation.h"

//class for the station refit menu
class HangarTab : public MenuTab
{
public:
	HangarTab(IGUITabControl *tabs, Player *player);
	~HangarTab();
	virtual void run(SpaceStation *target);

protected:
	void loadInventories();
	void loadWeaponLists();
	void refitWeapons();

	Player *player;

	IGUIComboBox *heavySlot;
	IGUIComboBox *heavySlotWeapon;

	IGUIComboBox *mediumSlot;
	IGUIComboBox *mediumSlotWeapon;

	IGUIComboBox *lightSlot;
	IGUIComboBox *lightSlotWeapon;

	IGUIButton *refit;
	IGUIButton *repair;

	int currentSelection[4];
};

#endif
