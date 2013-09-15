#include "stdafx.h"
#include "shiptab.h"

ShipTab::ShipTab(gui::IGUITabControl *tabs, Player* player)
	: player(player)
{
	tab = tabs->addTab(L"Ship");

	//creating
	guienv->addStaticText(L"", core::rect<s32>(10,20,iWidth-10,100), false, true, tab); // shiptxt
	guienv->addStaticText(L"", core::rect<s32>(10,60,iWidth-10,100), false, true, tab); // description
	guienv->addStaticText(L"Ship Subsystems", core::rect<s32>(10,120,iWidth-10,iHeight-10), false, true, tab); // subsystems
	IGUIListBox* systems_list = guienv->addListBox(core::rect<s32>(20,140,(iWidth/2)-125,iHeight-20), tab); // systems_list
	guienv->addStaticText(L"Integrity : ", core::rect<s32>(iWidth/2-115,140,iHeight-40,220), false, true, tab); // systems_health
	guienv->addStaticText(L"Crew Required : ", core::rect<s32>(iWidth/2-115,200,iWidth-40,220), false, true, tab); // crew_req
	guienv->addStaticText(L"Crew Available : ", core::rect<s32>(iWidth/2-115,170,iWidth-40,190), false, true, tab); // crew_avail
	guienv->addButton(core::rect<s32>(iWidth-460,iHeight-205,iWidth-360,iHeight-185), tab, -1,L"Repair"); // repair
	guienv->addButton(core::rect<s32>(iWidth-340,iHeight-205,iWidth-240,iHeight-185), tab, -1,L"Replace"); // replace

	//initializing
	for (unsigned i = 0; i < player->getInfo().subsystems.size(); ++i) {
		systems_list->addItem(player->getInfo().subsystems[i].name.c_str());
	}
}

ShipTab::~ShipTab()
{
}

void ShipTab::run()
{
}
