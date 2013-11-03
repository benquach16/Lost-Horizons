#include "stdafx.h"
#include "shiptab.h"
#include "globals.h"

using namespace base;

ShipTab::ShipTab(IGUITabControl *tabs, Player* player)
	: MenuTab(tabs->addTab(L"Ship")), player(player)
{
	//creating
	shipName = guienv->addStaticText(L"", rect<s32>(10,20,490,100), false, true, tab); // shiptxt
	description = guienv->addStaticText(L"", rect<s32>(10,50,490,90), false, true, tab); // description
	guienv->addStaticText(L"Ship Subsystems", rect<s32>(10,100,490,120), false, true, tab); // subsystems
	systemsList = guienv->addListBox(rect<s32>(20,120,400,440), tab); // systems_list
	systemsHealth = guienv->addStaticText(L"Integrity : ", rect<s32>(410,120,800,140), false, true, tab); // systems_health
	crewRq = guienv->addStaticText(L"Crew Required : ", rect<s32>(410,180,800,200), false, true, tab); // crew_req
	crewAv = guienv->addStaticText(L"Crew Available : ", rect<s32>(410,150,800,170), false, true, tab); // crew_avail
	repair = guienv->addButton(rect<s32>(560,450,660,470), tab, -1,L"Repair"); // repair
	replace = guienv->addButton(rect<s32>(680,450,780,470), tab, -1,L"Replace"); // replace
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
	shipName->setText(player->getName());
	description->setText(player->getDesc());

	//replace the string -- crew available
	crewAv->setText((core::stringw(L"Crew Available : ") + core::stringw(player->getInfo().crew)).c_str());

	int index = systemsList->getSelected();
	if (index >= 0)
	{
		//replace the string -- health
		systemsHealth->setText((core::stringw(L"Integrity : ") + core::stringw(player->getSubsystems()[index]) + L"%").c_str());
	}

	//replace the string -- crew required
	if (index >= 0 && index < SUBSYSTEM_COUNT)
	{
		int repairCount = 5*(100 - player->getSubsystems()[index]);
		crewRq->setText((core::stringw(L"Crew Required : ") + core::stringw(repairCount)).c_str());

		if (repair->isPressed() && repairCount < player->getInfo().crew)
			player->getSubsystems()[index] = 100;
	}
}
