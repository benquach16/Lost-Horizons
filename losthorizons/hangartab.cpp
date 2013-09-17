#include "stdafx.h"
#include "hangartab.h"

HangarTab::HangarTab(gui::IGUITabControl *tabs, Player *player) : MenuTab(), player(player),
	heavySlot(0), heavySlotWeapon(0), mediumSlot(0), mediumSlotWeapon(0), lightSlot(0), lightSlotWeapon(0)
{
	tab = tabs->addTab(L"Hangar");
	//add hangar stuff
	//hangar allows the player to refit his ship
	//and repair
	guienv->addStaticText(L"Slot", rect<s32>(20,20,60,40), false, true, tab);
	heavySlot = guienv->addComboBox(rect<s32>(20,40,60,60),tab);
	heavySlotWeapon = guienv->addComboBox(rect<s32>(70,40,170,60),tab);
	mediumSlot = guienv->addComboBox(rect<s32>(20,80,60,100), tab);
}

HangarTab::~HangarTab()
{

}

void HangarTab::run()
{

}
