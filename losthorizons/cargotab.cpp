#include "stdafx.h"
#include "cargotab.h"

CargoTab::CargoTab(gui::IGUITabControl *tabs, Player* player)
	: player(player)
{
	tab = tabs -> addTab(L"Cargo");

	//creating
	guienv->addStaticText(L"Cost", core::rect<s32>(10,10,190,30), false, true, tab); // list title1
	costList = guienv->addListBox(core::rect<s32>(0,10,100,440), tab); // cost
	guienv->addStaticText(L"Weight", core::rect<s32>(110,10,190,30), false, true, tab); // list title2
	weightList = guienv->addListBox(core::rect<s32>(100,10,200,440), tab); // weight
	guienv->addStaticText(L"Description", core::rect<s32>(210,10,790,30), false, true, tab); // list title3
	descriptionList = guienv->addListBox(core::rect<s32>(200,10,800,440), tab); // description
}

CargoTab::~CargoTab()
{
}

void CargoTab::run()
{
}