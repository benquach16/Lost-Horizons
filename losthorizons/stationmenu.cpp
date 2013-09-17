#include "stdafx.h"
#include "stationmenu.h"

StationMenu::StationMenu(Player *player) : MenuWindow(), tabs(0), player(player)
{
	window = guienv->addWindow(rect<s32>(iWidth/2-400,iHeight/2-260,iWidth/2+400,iHeight/2+260), true, L"Space Station");
	window->getCloseButton()->setVisible(false);
	window->setDrawBackground(false);
	// this is terrible. make consistent with the new way we do menutabs as shown in gamemenu and shiptab
	tabs = guienv->addTabControl(rect<s32>(0,0,iWidth/2+800,iHeight/2+600), window, true);
	initializeDisplay();
	window->setVisible(false);
}

StationMenu::~StationMenu()
{
}

void StationMenu::run(const TargetableObject *target)
{
	MenuWindow::run();
	store->run();
	hangar->run();
	//if(target && target->getTargetableObjectType() == E_OBJECT_SPACESTATION)
	{
		//SpaceStation *stationTarget = (SpaceStation*)target;

		//runStore();
	}
}

//protected function
void StationMenu::initializeDisplay()
{
	store = new StoreTab(tabs, player);
	hangar = new HangarTab(tabs, player);

}
