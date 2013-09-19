#include "stdafx.h"
#include "cargotab.h"

CargoTab::CargoTab(gui::IGUITabControl *tabs, Player* player)
	: player(player)
{
	tab = tabs -> addTab(L"Cargo");

	//creating
	guienv->addStaticText(L"Items", core::rect<s32>(10,10,190,30), false, true, tab); // list title1
	itemList = guienv->addListBox(core::rect<s32>(0,10,200,440), tab); // items
	guienv->addStaticText(L"Cost", core::rect<s32>(210,10,290,30), false, true, tab); // list title2
	costList = guienv->addListBox(core::rect<s32>(200,10,300,440), tab); // cost
	guienv->addStaticText(L"Weight", core::rect<s32>(310,10,390,30), false, true, tab); // list title3
	weightList = guienv->addListBox(core::rect<s32>(300,10,400,440), tab); // weight
	guienv->addStaticText(L"Description", core::rect<s32>(410,10,790,30), false, true, tab); // list title4
	descriptionList = guienv->addListBox(core::rect<s32>(400,10,800,440), tab); // description
}

CargoTab::~CargoTab()
{
}

void CargoTab::run()
{
}