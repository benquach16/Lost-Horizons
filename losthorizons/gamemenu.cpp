#include "stdafx.h"
#include "gamemenu.h"
#include "globals.h"

using namespace base;

GameMenu::GameMenu(Player* player, MissionManager *missionManager)
	: MenuWindow(guienv->addWindow(rect<s32>(width/2-400,height/2-260,width/2+400,height/2+260), true)),
	  tabs(guienv->addTabControl(rect<s32>(0,0,width/2+800,height/2+600), window, true)),
	  player(player), missionManager(missionManager)
{
	window->getCloseButton()->setVisible(false);
	window->setDrawBackground(false);

	initializeDisplay();
	window->setVisible(false);
}

//virtual destructor called in some base
GameMenu::~GameMenu()
{
	delete ship;
	delete cargo;
	delete mission;
}

void GameMenu::run()
{
	MenuWindow::run();
	ship->run();
	cargo->run();
	mission->run();
}

void GameMenu::initializeDisplay()
{
	ship = new ShipTab(tabs, player);
	cargo = new CargoTab(tabs, player);
	mission = new MissionTab(tabs, missionManager);
}
