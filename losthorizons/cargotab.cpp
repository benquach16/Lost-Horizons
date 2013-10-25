#include "stdafx.h"
#include "cargotab.h"
#include "globals.h"

using namespace base;

CargoTab::CargoTab(IGUITabControl *tabs, Player* player)
	: MenuTab(tabs->addTab(L"Cargo")), player(player)
{
	//creating
	guienv->addStaticText(L"Items", rect<s32>(10,10,190,30), false, true, tab); // list title1
	guienv->addStaticText(L"Cost", rect<s32>(210,10,290,30), false, true, tab); // list title2
	guienv->addStaticText(L"Weight", rect<s32>(310,10,390,30), false, true, tab); // list title3
	guienv->addStaticText(L"Description", rect<s32>(410,10,790,30), false, true, tab); // list title4

	itemList = guienv->addListBox(rect<s32>(0,30,200,440), tab); // items
	costTxtBox = guienv->addStaticText(L"", rect<s32>(200,30,300,440), true, true, tab); // cost
	weightTxtBox = guienv->addStaticText(L"", rect<s32>(300,30,400,440), true, true, tab); // weight
	descriptionTxtBox = guienv->addStaticText(L"", rect<s32>(400,30,790,440), true, true, tab); //description
}

CargoTab::~CargoTab()
{
}

void CargoTab::run()
{
	//updating the listboxes
	//comparing item count in listbox and the actual ITEM LIST
	//if different, something must've changed
	if (itemList->getItemCount() != player->getInventory().getConvertedInventory().size())
		itemListUpdate();
	showItemInfo();
}

void CargoTab::itemListUpdate()
{
	//clears the listbox
	itemList->clear();

	//updates the actual ITEM LIST onto listbox
	for (unsigned i = 0; i < player->getInventory().getConvertedInventory().size(); ++i)
		itemList->addItem(player->getInventory().getConvertedInventory().at(i).c_str());
}

void CargoTab::showItemInfo()
{
	//setting the stats
	int index = itemList->getSelected();
	if (index != -1)
	{
		//clearing the textboxes
		costTxtBox->setText(L"");
		weightTxtBox->setText(L"");
		descriptionTxtBox->setText(L"");

		//declaring txt variables for info of an item when selected
		stringw costTxt, weightTxt, descriptionTxt;

		//initializing
		std::vector<ObjectManager::E_ITEM_LIST> syncedInventory = player->getInventory().getConvertedInventoryNoSpaces();
		costTxt = static_cast<stringw>( ObjectManager::itemList[syncedInventory[index]]->getPrice()) + " Credits";
		weightTxt = static_cast<stringw>(ObjectManager::itemList[syncedInventory[index]]->getWeight()) + " Kg";
		descriptionTxt =ObjectManager::itemList[syncedInventory[index]]->getDesc().c_str();

		//fill in the testboxes
		costTxtBox->setText(costTxt.c_str());
		weightTxtBox->setText(weightTxt.c_str());
		descriptionTxtBox->setText(descriptionTxt.c_str());
	}
}
