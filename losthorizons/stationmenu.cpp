#include "stdafx.h"
#include "stationmenu.h"

StationMenu::StationMenu() : MenuWindow(), tabs(0)
{
	window = guienv->addWindow(rect<s32>(iWidth/2-400,iHeight/2-300,iWidth/2+400,iHeight/2+300), true, L"Space Station");
	window->setDrawTitlebar(false);
	window->getCloseButton()->setVisible(false);
	window->setDrawBackground(false);

	tabs = guienv->addTabControl(rect<s32>(0,0,iWidth/2+800,iHeight/2+600), window, true);
	store = tabs->addTab(L"Store");
	hanger = tabs->addTab(L"Hanger");
	missions = tabs->addTab(L"Missions");
	shipyard = tabs->addTab(L"Shipyard");
	people = tabs->addTab(L"People");

	window->setVisible(false);

	initializeDisplay();
}

StationMenu::~StationMenu()
{
}

void StationMenu::run(const TargetableObject *target, Player *player)
{
	MenuWindow::run();
}

//protected function
void StationMenu::initializeDisplay()
{
	storePointers.playerInventory = guienv->addListBox(rect<s32>(20,40, 380, 400), store);
	guienv->addListBox(rect<s32>(420, 40, 780, 400), store);
	guienv->addStaticText(L"Your Cargo", rect<s32>(20,20,380,40), false, true, store);
	guienv->addStaticText(L"For Sale", rect<s32>(420, 20, 780, 40), false, true, store);
	guienv->addStaticText(L"", rect<s32>(20, 420, 380, 440), false, true, store);

}
