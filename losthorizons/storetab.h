#ifndef _STORETAB_H_
#define _STORETAB_H_

#include "irrlicht.h"
#include "menutab.h"

using namespace irr;
using namespace core;
using namespace gui;

//create a class for each tab
//this class is meant for use by the stationmenu class
class StoreTab : public MenuTab
{
public:
	StoreTab(gui::IGUITabControl *tabs, Player *player);
	~StoreTab();
	virtual void run();
protected:
	Player *player;
	void loadInventories();

	gui::IGUIListBox *playerInventory;
	gui::IGUIListBox *stationInventory;
	gui::IGUIStaticText *selectedValue;
	gui::IGUIStaticText *selectedWeight;
	gui::IGUIStaticText *selectedDescription;
	gui::IGUIButton *buyButton;
	gui::IGUIButton *sellButton;
	gui::IGUIStaticText *playerCash;

};

#endif
