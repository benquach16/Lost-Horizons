#include "stdafx.h"
#include "hangartab.h"
#include "globals.h"
#include <iostream>

using namespace base;

HangarTab::HangarTab(IGUITabControl *tabs, Player *player)
	: MenuTab(tabs->addTab(L"Hangar")), player(player),
	  heavySlot(0), heavySlotWeapon(0), mediumSlot(0), mediumSlotWeapon(0), lightSlot(0), lightSlotWeapon(0), 
	  repair(0), refit(0)
{
	//add hangar stuff
	//hangar allows the player to refit his ship
	//and repair
	guienv->addStaticText(L" Slot", rect<s32>(20,20,60,40), false, true, tab);
	heavySlot = guienv->addComboBox(rect<s32>(20,40,60,60),tab);
	heavySlotWeapon = guienv->addComboBox(rect<s32>(70,40,270,60),tab);

	guienv->addStaticText(L" Slot", rect<s32>(20,60,60,80), false, true, tab);
	mediumSlot = guienv->addComboBox(rect<s32>(20,80,60,100), tab);
	mediumSlotWeapon = guienv->addComboBox(rect<s32>(70,80,270,100), tab);

	guienv->addStaticText(L" Slot", rect<s32>(20,100,60,120), false, true, tab);
	lightSlot = guienv->addComboBox(rect<s32>(20,120,60,140), tab);
	lightSlotWeapon = guienv->addComboBox(rect<s32>(70,120,270,140), tab);

	refit = guienv->addButton(rect<s32>(290,40,390,60), tab, -1, L"Refit");
	repair = guienv->addButton(rect<s32>(680, 480, 780, 500), tab, -1, L"Repair");
}

HangarTab::~HangarTab()
{

}

void HangarTab::run(SpaceStation *target)
{
	//run thru everything
	loadInventories();
	loadWeaponLists();

	if (refit->isPressed())
	{
		refitWeapons();
	}
	if (repair->isPressed())
	{
		int cost = player->getInfo().maxHull - player->getInfo().hull;
		if(player->getInventory().getCredits() > cost)
		{
			player->repairShip();
			player->getInventory().addCredits(-cost);
		}
	}
}

//protected function
void HangarTab::loadInventories()
{
	//if they're empty make sure we refill them
	if (!heavySlot->getItemCount())
	{
		for (unsigned i = 0; i < player->getTurrets(TURRET_HEAVY).size(); ++i)
		{
			heavySlot->addItem(std::to_wstring(i).c_str());
		}
	}
	if (!mediumSlot->getItemCount())
	{
		for (unsigned i = 0; i < player->getTurrets(TURRET_MEDIUM).size(); ++i)
		{
			mediumSlot->addItem(std::to_wstring(i).c_str());
		}
	}
	if (!lightSlot->getItemCount())
	{
		for (unsigned i = 0; i < player->getTurrets(TURRET_LIGHT).size(); ++i)
		{
			lightSlot->addItem(std::to_wstring(i).c_str());
		}
	}
}

//protected function
void HangarTab::loadWeaponLists()
{
	//update the combobox to allow the player to choose weapons
	//create unique lists for each weaponslot

	if (mediumSlot->getSelected() != -1)
	{
		if (!mediumSlotWeapon->getItemCount())
		{
			std::vector<ObjectManager::E_ITEM_LIST> weaponsList = player->getInventory().getMediumWeapons();
			for (unsigned i = 0; i < weaponsList.size(); i++)
			{
				mediumSlotWeapon->addItem(ObjectManager::itemList[weaponsList[i]]->getName());
			}
		}
	}
	if (lightSlot->getSelected() != -1)
	{
		if (!lightSlotWeapon->getItemCount())
		{
			std::vector<ObjectManager::E_ITEM_LIST> weaponsList = player->getInventory().getLightWeapons();
			for (unsigned i = 0; i < weaponsList.size(); i++)
			{
				lightSlotWeapon->addItem(ObjectManager::itemList[weaponsList[i]]->getName());
			}
		}
	}
}

void HangarTab::refitWeapons()
{
	//refit for currently selected slot
	//add the item back to inventory
	std::vector<ObjectManager::E_ITEM_LIST> weaponsList = player->getInventory().getMediumWeapons();
	player->getInventory().addItem(player->getTurrets(TURRET_MEDIUM)[mediumSlot->getSelected()]->getTurretType(), 1);
	player->getInventory().removeItem(weaponsList[mediumSlotWeapon->getSelected()]);
	player->setMediumTurret(weaponsList[mediumSlotWeapon->getSelected()], mediumSlot->getSelected());

	mediumSlotWeapon->clear();
	mediumSlot->clear();
	
	weaponsList = player->getInventory().getLightWeapons();
	player->getInventory().addItem(player->getTurrets(TURRET_LIGHT)[lightSlot->getSelected()]->getTurretType(), 1);
	player->getInventory().removeItem(weaponsList[lightSlotWeapon->getSelected()]);
	player->setLightTurret(weaponsList[lightSlotWeapon->getSelected()], lightSlot->getSelected());

	lightSlotWeapon->clear();
	lightSlot->clear();
}
