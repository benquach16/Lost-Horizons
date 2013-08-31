#ifndef _STATIONMENU_H_
#define _STATIONMENU_H_

#include "player.h"
#include "spacestation.h"
#include "menuwindow.h"

//ui menu that is opened when the player is docked at a space staiton
class StationMenu : public MenuWindow
{
public:
	StationMenu(Player *player);
	virtual ~StationMenu();
	void run(const TargetableObject *target);
	
protected:
	void initializeDisplay();
	void loadInventories();
	void runStore();
	void runHanger();
	void runMissions();
	void runShipyard();
	void runPeople();
	Player *player;

	gui::IGUITabControl *tabs;
	gui::IGUITab *store;
	//we need a way to organize all these pointers between all these tabs
	//store tab pointers
	gui::IGUIListBox *playerInventory;
	gui::IGUIListBox *stationInventory;
	gui::IGUIStaticText *selectedValue;
	gui::IGUIStaticText *selectedWeight;
	gui::IGUIStaticText *selectedDescription;
	gui::IGUIButton *buyButton;
	gui::IGUIButton *sellButton;
	gui::IGUIStaticText *playerCash;

	gui::IGUITab *hanger;
	gui::IGUITab *missions;
	gui::IGUITab *shipyard;
	gui::IGUITab *people;
};

#endif
