#include "stdafx.h"
#include "storetab.h"

StoreTab::StoreTab(gui::IGUITabControl *tabs, Player *player) : MenuTab(), player(player)
{
	//initialize this
	tab = tabs->addTab(L"Store");
	playerInventory = guienv->addListBox(rect<s32>(20,40, 380, 300), tab);
	stationInventory = guienv->addListBox(rect<s32>(420, 40, 780, 300), tab);
	guienv->addStaticText(L"Your Cargo", rect<s32>(20,20,380,40), false, true, tab);
	guienv->addStaticText(L"For Sale", rect<s32>(420, 20, 780, 40), false, true, tab);
	selectedValue = guienv->addStaticText(L"Value :", rect<s32>(400, 320, 600, 340), false, true, tab);
	selectedWeight = guienv->addStaticText(L"Weight :", rect<s32>(620, 320, 780, 340), false, true, tab);
	selectedDescription = guienv->addStaticText(L"", rect<s32>(20, 360, 780, 400), false, true, tab);
	sellButton = guienv->addButton(rect<s32>(20,420,120,440), tab, -1, L"Sell");
	buyButton = guienv->addButton(rect<s32>(680, 420, 780, 440), tab, -1, L"Buy");
	playerCash = guienv->addStaticText(L"Your Credits :", rect<s32>(140, 420, 440, 440), false, true, tab);
}

StoreTab::~StoreTab()
{
}

void StoreTab::run(SpaceStation *target)
{
	//run through the store tab
	//uis tend to have a ton of bloated code
	loadInventories(target);

	std::wstring str(L"Your Credits :");
	str += std::to_wstring(player->getInfo().inventory.getCredits());
	playerCash->setText(str.c_str());
	int i = playerInventory->getSelected();
	if(i != -1)
	{
		//has something selected so we load its information
		std::wstring tmp(L"Value :");
		tmp += std::to_wstring(player->getInfo().inventory[i].getPrice());
		selectedValue->setText(tmp.c_str());
		tmp = L"Weight :";
		tmp += std::to_wstring(player->getInfo().inventory[i].getWeight());
		selectedWeight->setText(tmp.c_str());
		selectedDescription->setText(player->getInfo().inventory[i].getDesc().c_str());

		if(sellButton->isPressed())
		{
			//sell selected item
			player->getInventory().addCredits(player->getInfo().inventory[i].getPrice());
			target->getInventory().addItem(player->getInfo().inventory[i], 1);
			player->getInventory().removeItem(i);
			playerInventory->clear();
			stationInventory->clear();
		}
	}
	else
	{
		//reset text if nothing is selected
		selectedValue->setText(L"Value :");
		selectedWeight->setText(L"Weight :");
		selectedDescription->setText(L"");
	}
	i = stationInventory->getSelected();
	if(i != -1)
	{
		//has something selected so we load its information
		std::wstring tmp(L"Value :");
		tmp += std::to_wstring(target->getInfo().inventory[i].getPrice());
		selectedValue->setText(tmp.c_str());
		tmp = L"Weight :";
		tmp += std::to_wstring(target->getInfo().inventory[i].getWeight());
		selectedWeight->setText(tmp.c_str());
		selectedDescription->setText(target->getInfo().inventory[i].getDesc().c_str());
		if(buyButton->isPressed())
		{
			//sell selected item
			ItemProperties t = target->getInfo().inventory[i];
			player->getInventory().addCredits(-t.getPrice());
			player->getInventory().addItem(t, 1);
			target->getInventory().removeItem(i);
			playerInventory->clear();
			stationInventory->clear();
		}
	}
}

//protected function
void StoreTab::loadInventories(SpaceStation *target)
{
	//updating is slow!
	//only update when something is for sure changed!
	std::vector<std::wstring> data = player->getInfo().inventory.getConvertedInventory();

	if(!playerInventory->getItemCount())
	{
		for(unsigned i = 0; i < data.size(); i++)
		{
			playerInventory->addItem(data[i].c_str());
		}
	}

	data = target->getInfo().inventory.getConvertedInventory();
	if(!stationInventory->getItemCount())
	{
		for(unsigned i = 0; i < data.size(); i++)
		{
			stationInventory->addItem(data[i].c_str());
		}		
	}
}
