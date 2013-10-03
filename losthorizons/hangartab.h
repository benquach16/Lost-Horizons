#ifndef _HANGARTAB_H_
#define _HANGARTAB_H_

#include "menutab.h"

//class for the station refit menu
class HangarTab : public MenuTab
{
public:
	HangarTab(gui::IGUITabControl *tabs, Player *player);
	~HangarTab();
	virtual void run(SpaceStation *target);

protected:
	void loadInventories();
	void loadWeaponLists();
	void refitWeapons();

	Player *player;

	gui::IGUIComboBox *heavySlot;
	gui::IGUIComboBox *heavySlotWeapon;

	gui::IGUIComboBox *mediumSlot;
	gui::IGUIComboBox *mediumSlotWeapon;

	gui::IGUIComboBox *lightSlot;
	gui::IGUIComboBox *lightSlotWeapon;

	gui::IGUIButton *refit;
	gui::IGUIButton *repair;

	int currentSelection[4];
};

#endif
