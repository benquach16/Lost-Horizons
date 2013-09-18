#include "stdafx.h"
#include "shiptab.h"

ShipTab::ShipTab(gui::IGUITabControl *tabs, Player* player)
	: player(player)
{
	tab = tabs->addTab(L"Ship");

	//creating
	shipName = guienv->addStaticText(L"", core::rect<s32>(10,20,iWidth-10,100), false, true, tab); // shiptxt
	description = guienv->addStaticText(L"", core::rect<s32>(10,60,iWidth-10,100), false, true, tab); // description
	guienv->addStaticText(L"Ship Subsystems", core::rect<s32>(10,120,iWidth-10,iHeight-10), false, true, tab); // subsystems
	systemsList = guienv->addListBox(core::rect<s32>(20,140,(iWidth/2)-125,iHeight-20), tab); // systems_list
	systemsHealth = guienv->addStaticText(L"Integrity : ", core::rect<s32>(iWidth/2-115,140,iHeight-40,220), false, true, tab); // systems_health
	crewRq = guienv->addStaticText(L"Crew Required : ", core::rect<s32>(iWidth/2-115,200,iWidth-40,220), false, true, tab); // crew_req
	crewAv = guienv->addStaticText(L"Crew Available : ", core::rect<s32>(iWidth/2-115,170,iWidth-40,190), false, true, tab); // crew_avail
	repair = guienv->addButton(core::rect<s32>(iWidth-460,iHeight-205,iWidth-360,iHeight-185), tab, -1,L"Repair"); // repair
	replace = guienv->addButton(core::rect<s32>(iWidth-340,iHeight-205,iWidth-240,iHeight-185), tab, -1,L"Replace"); // replace

	//initializing
	for (unsigned i = 0; i < player->getInfo().subsystems.size(); ++i)
		systemsList->addItem(player->getInfo().subsystems[i].name.c_str());

}

ShipTab::~ShipTab()
{
}

void ShipTab::run()
{
	textUpdate();
}

//HELPER FUNCTIONS
void ShipTab::textUpdate()
{
	shipName -> setText(player -> getName().c_str());
	description -> setText(player -> getDesc().c_str());

	//replace the string -- crew available
	stringw crewAvStr = L"Crew Available : ";
	crewAvStr += player -> getInfo().crew;
	crewAv -> setText(crewAvStr.c_str());

	int index = systemsList->getSelected();
	if(index >= 0)
	{
		//access the sub menu at index tmp
		systemsList[index];
		//replace the string -- health
		stringw systemsHealthStr = L"Integrity: ";
		systemsHealthStr += player -> getInfo().subsystems.at(index).health;
		systemsHealth -> setText(systemsHealthStr.c_str());
	}

	//replace the string -- crew required
	stringw crewReqStr = L"Crew Required : ";
	if(index >= 0 && index < static_cast<int>(player -> getInfo().subsystems.size()))
	{
		int repairCount = 5 * (100 - player -> getInfo().subsystems.at(index).health);
		crewReqStr += repairCount;
		crewRq -> setText(crewReqStr.c_str());

		if(repair -> isPressed())
			if(repairCount < player -> getInfo().crew)
				player -> getSubsystem(index).health = 100;
	}
	

}