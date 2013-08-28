#ifndef _STATIONMENU_H_
#define _STATIONMENU_H_

#include "player.h"
#include "spacestation.h"
#include "menuwindow.h"

//ui menu that is opened when the player is docked at a space staiton
class StationMenu : public MenuWindow
{
public:
	StationMenu();
	virtual ~StationMenu();
	void run(const TargetableObject *target, Player *player);
	
protected:
	void initializeDisplay();

	gui::IGUITabControl *tabs;
	gui::IGUITab *store;
	//we need a way to organize all these pointers between all these tabs
	//so throw them in pointers
	struct storePointersStruct
	{
		gui::IGUIListBox *playerInventory;
		gui::IGUIListBox *stationInventory;
	};
	storePointersStruct storePointers;
	gui::IGUITab *hanger;
	gui::IGUITab *missions;
	gui::IGUITab *shipyard;
	gui::IGUITab *people;
};

#endif
