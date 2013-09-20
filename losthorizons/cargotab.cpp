#include <vector>

#include "stdafx.h"
#include "cargotab.h"

CargoTab::CargoTab(gui::IGUITabControl *tabs, Player* player)
	: player(player)
{
	tab = tabs -> addTab(L"Cargo");

	//creating
	guienv->addStaticText(L"Items", core::rect<s32>(10,10,190,30), false, true, tab); // list title1
	itemList = guienv->addListBox(core::rect<s32>(0,30,200,440), tab); // items
	guienv->addStaticText(L"Cost", core::rect<s32>(210,10,290,30), false, true, tab); // list title2
	costList = guienv->addListBox(core::rect<s32>(200,30,300,440), tab); // cost
	guienv->addStaticText(L"Weight", core::rect<s32>(310,10,390,30), false, true, tab); // list title3
	weightList = guienv->addListBox(core::rect<s32>(300,30,400,440), tab); // weight
	guienv->addStaticText(L"Description", core::rect<s32>(410,10,790,30), false, true, tab); // list title4
	descriptionList = guienv->addListBox(core::rect<s32>(400,30,800,440), tab); // description
}

CargoTab::~CargoTab()
{
}

void CargoTab::run()
{
	//updating the listboxes
	//comparing item count in listbox and the actual ITEM LIST
	//if different, something must've changed
	if(itemList -> getItemCount() != player -> getInventory().getConvertedInventory().size())
		itemListUpdate();
	showItemInfo();
}

void CargoTab::itemListUpdate()
{
	//clears the listbox
	itemList -> clear();

	//updates the actual ITEM LIST onto listbox
	for(unsigned i = 0; i < player -> getInventory().getConvertedInventory().size(); ++i)
		itemList -> addItem(player -> getInventory().getConvertedInventory().at(i).c_str());
}

void CargoTab::showItemInfo()
{
	//resetting the info listboxes when looped
	costList -> clear();
	weightList -> clear();
	descriptionList -> clear();

	//setting the stats
	int index = itemList -> getSelected();
	if(index != -1)
	{
		//declaring txt variables for info of an item when selected
		stringw costTxt, weightTxt, descriptionTxt;

		//initializing
		costTxt = static_cast<stringw>(player -> getInventory().getItemPropertiesPtr().at(index) -> getPrice()) + " Credits";
		weightTxt = static_cast<stringw>(player -> getInventory().getItemPropertiesPtr().at(index) -> getWeight()) + " Kg";
		descriptionTxt = player -> getInventory().getItemPropertiesPtr().at(index) -> getDesc().c_str();

		//add them to listboxes accordingly
		costList -> addItem(costTxt.c_str());
		weightList -> addItem(weightTxt.c_str());
		descriptionList -> addItem(descriptionTxt.c_str());
	}
}