#include "stdafx.h"
#include "cargotab.h"

CargoTab::CargoTab(gui::IGUITabControl *tabs, Player* player)
	: player(player)
{
	tab = tabs -> addTab(L"Cargo");

	//creating
	//continue
	//IGUIListBox* systems_list = guienv->addListBox(core::rect<s32>(20,140,(iWidth/2)-125,iHeight-20), tab); // systems_list
}

CargoTab::~CargoTab()
{
}

void CargoTab::run()
{
}