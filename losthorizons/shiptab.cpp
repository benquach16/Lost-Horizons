#include "stdafx.h"
#include "shiptab.h"

ShipTab::ShipTab(gui::IGUITabControl *tabs, Player* player)
	: player(player)
{
	tab = tabs->addTab(L"Ship");

	//creating
	shipName = guienv->addStaticText(L"", core::rect<s32>(10,20,490,100), false, true, tab); // shiptxt
	description = guienv->addStaticText(L"", core::rect<s32>(10,50,490,90), false, true, tab); // description
	guienv->addStaticText(L"Ship Subsystems", core::rect<s32>(10,100,490,120), false, true, tab); // subsystems
	systemsList = guienv->addListBox(core::rect<s32>(20,120,400,440), tab); // systems_list
	systemsHealth = guienv->addStaticText(L"Integrity : ", core::rect<s32>(410,120,800,140), false, true, tab); // systems_health
	crewRq = guienv->addStaticText(L"Crew Required : ", core::rect<s32>(410,180,800,200), false, true, tab); // crew_req
	crewAv = guienv->addStaticText(L"Crew Available : ", core::rect<s32>(410,150,800,170), false, true, tab); // crew_avail
	repair = guienv->addButton(core::rect<s32>(560,450,660,470), tab, -1,L"Repair"); // repair
	replace = guienv->addButton(core::rect<s32>(680,450,780,470), tab, -1,L"Replace"); // replace
	//replace not used in txtupdate function
	//CONTINUE

	//initializing
	for (unsigned i = 0; i < SUBSYSTEM_COUNT; ++i)
		systemsList->addItem(Ship::subsystemNames[i].c_str());
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
	shipName->setText(player->getName().c_str());
	description->setText(player->getDesc().c_str());

	//replace the string -- crew available
	stringw crewAvStr = L"Crew Available : ";
	crewAvStr += player->getInfo().crew;
	crewAv->setText(crewAvStr.c_str());

	int index = systemsList->getSelected();
	if (index >= 0)
	{
		//replace the string -- health
		stringw systemsHealthStr = L"Integrity : ";
		systemsHealthStr += player->getSubsystems()[index];
		systemsHealthStr += L"%";
		systemsHealth->setText(systemsHealthStr.c_str());
	}

	//replace the string -- crew required
	stringw crewReqStr = L"Crew Required : ";
	if (index >= 0 && index < SUBSYSTEM_COUNT)
	{
		int repairCount = 5 * (100 - player->getSubsystems()[index]);
		crewReqStr += repairCount;
		crewRq->setText(crewReqStr.c_str());

		if(repair->isPressed())
			if(repairCount < player->getInfo().crew)
				player->getSubsystems()[index] = 100;
	}

}
