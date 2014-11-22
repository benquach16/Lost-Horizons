#include "stdafx.h"
#include "stationmenu.h"
#include "globals.h"

using namespace base;

StationMenu::StationMenu(Ship *player)
	: MenuWindow(guienv->addWindow(rect<s32>(width/2-400,height/2-260,width/2+400,height/2+260), true)),
	  tabs(guienv->addTabControl(rect<s32>(0,0,width/2+800,height/2+600), window, true)),
	  store(new StoreTab(tabs, player->getInventory())), hangar(new HangarTab(tabs, player)), job(new JobTab(tabs))
{
	window->getCloseButton()->setVisible(false);
	window->setDrawBackground(false);
	window->setVisible(false);
}

StationMenu::~StationMenu()
{
	delete store;
	delete hangar;
}

void StationMenu::run()
{
	store->run(((SpaceStation*)target)->getInventory());
	hangar->run();
}

void StationMenu::setTarget(TargetableObject *newTarget)
{
	target = newTarget;
}
