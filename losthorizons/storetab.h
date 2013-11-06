#ifndef _STORETAB_H_
#define _STORETAB_H_

#include "menutab.h"
#include "inventory.h"

//create a class for each tab
//this class is meant for use by the stationmenu class
class StoreTab : public MenuTab
{
public:
	StoreTab(IGUITabControl *tabs, Inventory &playerData);
	~StoreTab();
	virtual void run(Inventory &stationData);

private:
	void loadInventories(std::vector<std::wstring> playerConverted, std::vector<std::wstring> stationConverted);

	IGUIListBox *playerInventory;
	IGUIListBox *stationInventory;
	IGUIStaticText *selectedValue;
	IGUIStaticText *selectedWeight;
	IGUIStaticText *selectedDescription;
	IGUIButton *buyButton;
	IGUIButton *sellButton;
	IGUIStaticText *playerCash;

	Inventory &playerData;
};

#endif
