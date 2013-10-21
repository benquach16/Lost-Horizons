#ifndef _STORETAB_H_
#define _STORETAB_H_

#include "menutab.h"
#include "player.h"
#include "spacestation.h"

//create a class for each tab
//this class is meant for use by the stationmenu class
class StoreTab : public MenuTab
{
public:
	StoreTab(IGUITabControl *tabs, Player *player);
	~StoreTab();
	virtual void run(SpaceStation *target);

protected:
	Player *player;
	void loadInventories(SpaceStation *target);

	IGUIListBox *playerInventory;
	IGUIListBox *stationInventory;
	IGUIStaticText *selectedValue;
	IGUIStaticText *selectedWeight;
	IGUIStaticText *selectedDescription;
	IGUIButton *buyButton;
	IGUIButton *sellButton;
	IGUIStaticText *playerCash;
};

#endif
