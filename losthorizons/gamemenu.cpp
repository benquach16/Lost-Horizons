#include "stdafx.h"
#include "gamemenu.h"

GameMenu::GameMenu(Player* player) : MenuWindow(), player(player)
{
	window = guienv->addWindow(rect<s32>(iWidth/2-400,iHeight/2-300,iWidth/2+400,iHeight/2+300), true, L"Player Ship");
	window->setDrawTitlebar(false);
	window->getCloseButton()->setVisible(false);
	window->setDrawBackground(false);

	tabs = guienv->addTabControl(rect<s32>(0,0,iWidth/2+800,iHeight/2+600), window, true);
	ship = tabs->addTab(L"Ship", 1);
	cargo = tabs->addTab(L"Cargo", 2);
	crew = tabs->addTab(L"Crew", 3);
	loadout = tabs->addTab(L"Loadout", 4);
	hangar = tabs->addTab(L"Hangar", 5);
	missionLog = tabs->addTab(L"Mission Log", 6);

	window->setVisible(false);

	initializeDisplay();
}

//virtual destructor called in some base
GameMenu::~GameMenu()
{
}

void GameMenu::run()
{
	MenuWindow::run();
}

void GameMenu::initializeDisplay()
{

}
