#include "stdafx.h"
#include "stationmenu.h"

StationMenu::StationMenu() : MenuWindow()
{
	window = guienv->addWindow(rect<s32>(iWidth/2-400,iHeight/2-300,iWidth/2+400,iHeight/2+300), true, L"Space Station");
	window->setDrawTitlebar(false);
	window->getCloseButton()->setVisible(false);
	window->setDrawBackground(false);

	tabs = guienv->addTabControl(rect<s32>(0,0,iWidth/2+800,iHeight/2+600), window, true);
	tabs->addTab(L"Store");
	tabs->addTab(L"Hanger");
	tabs->addTab(L"Missions");
	tabs->addTab(L"Shipyard");
	tabs->addTab(L"People");

	window->setVisible(false);
}

StationMenu::~StationMenu()
{
}

void StationMenu::run(const TargetableObject *target)
{
	MenuWindow::run();
}
