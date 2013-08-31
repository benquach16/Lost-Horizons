#include "stdafx.h"
#include "stationmenu.h"

StationMenu::StationMenu(Player *player) : MenuWindow(), tabs(0), player(player)
{
	window = guienv->addWindow(rect<s32>(iWidth/2-400,iHeight/2-300,iWidth/2+400,iHeight/2+300), true, L"Space Station");
	window->setDrawTitlebar(false);
	window->getCloseButton()->setVisible(false);
	window->setDrawBackground(false);

	tabs = guienv->addTabControl(rect<s32>(0,0,iWidth/2+800,iHeight/2+600), window, true);
	store = tabs->addTab(L"Store", 1);
	hanger = tabs->addTab(L"Hanger", 2);
	missions = tabs->addTab(L"Missions", 3);
	shipyard = tabs->addTab(L"Shipyard", 4);
	people = tabs->addTab(L"People", 5);

	window->setVisible(false);

	initializeDisplay();
}

StationMenu::~StationMenu()
{
}

void StationMenu::run(const TargetableObject *target)
{
	MenuWindow::run();
	//if(target && target->getTargetableObjectType() == E_OBJECT_SPACESTATION)
	{
		//SpaceStation *stationTarget = (SpaceStation*)target;

		runStore();
	}
}

//protected function
void StationMenu::initializeDisplay()
{
	playerInventory = guienv->addListBox(rect<s32>(20,40, 380, 400), store);
	stationInventory = guienv->addListBox(rect<s32>(420, 40, 780, 400), store);
	guienv->addStaticText(L"Your Cargo", rect<s32>(20,20,380,40), false, true, store);
	guienv->addStaticText(L"For Sale", rect<s32>(420, 20, 780, 40), false, true, store);
	selectedValue = guienv->addStaticText(L"Value :", rect<s32>(400, 420, 600, 440), false, true, store);
	selectedWeight = guienv->addStaticText(L"Weight :", rect<s32>(620, 420, 780, 440), false, true, store);
	selectedDescription = guienv->addStaticText(L"", rect<s32>(20, 460, 780, 500), false, true, store);
	sellButton = guienv->addButton(rect<s32>(20,520,120,540), store, -1, L"Sell");
	buyButton = guienv->addButton(rect<s32>(680, 520, 780, 540), store, -1, L"Buy");
	playerCash = guienv->addStaticText(L"Your Credits :", rect<s32>(140, 520, 440, 540), false, true, store);
}

//protected function
void StationMenu::loadInventories()
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
}

//protected function
void StationMenu::runStore()
{
	//run through the store tab
	//uis tend to have a ton of bloated code
	loadInventories();

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
			player->getInventory().removeItem(i);
			playerInventory->clear();
		}
	}
	else
	{
		//reset text if nothing is selected
		selectedValue->setText(L"Value :");
		selectedWeight->setText(L"Weight :");
		selectedDescription->setText(L"");
	}
}
