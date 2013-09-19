#include "stdafx.h"
#include "cargotab.h"

CargoTab::CargoTab(gui::IGUITabControl *tabs, Player* player)
	: player(player)
{
	tab = tabs -> addTab(L"Cargo");

	//creating
	guienv->addStaticText(L"Heavy Metals", core::rect<s32>(30,10,190,30), false, true, tab); // list title1
	heavyMetalList = guienv->addListBox(core::rect<s32>(20,10,200,440), tab); // heavy metals
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