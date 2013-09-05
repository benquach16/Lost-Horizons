#include "stdafx.h"
#include "stationmenu.h"

StationMenu::StationMenu(Player *player) : MenuWindow(), tabs(0), player(player)
{
	window = guienv->addWindow(rect<s32>(iWidth/2-400,iHeight/2-300,iWidth/2+400,iHeight/2+300), true, L"Space Station");
	window->setDrawTitlebar(false);
	window->getCloseButton()->setVisible(false);
	window->setDrawBackground(false);

	tabs = guienv->addTabControl(rect<s32>(0,0,iWidth/2+800,iHeight/2+600), window, true);
	//store = tabs->addTab(L"Store", 1);
	store = new StoreTab(tabs, player);
	hanger = tabs->addTab(L"Hanger", 2);
	missions = tabs->addTab(L"Missions", 3);
	shipyard = tabs->addTab(L"Shipyard", 4);
	people = tabs->addTab(L"People", 5);
	
	window->setVisible(false);

}

StationMenu::~StationMenu()
{
}

void StationMenu::run(const TargetableObject *target)
{
	MenuWindow::run();
	store->run();
	//if(target && target->getTargetableObjectType() == E_OBJECT_SPACESTATION)
	{
		//SpaceStation *stationTarget = (SpaceStation*)target;

		//runStore();
	}
}

