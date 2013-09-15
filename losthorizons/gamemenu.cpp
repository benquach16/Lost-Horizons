#include "stdafx.h"
#include "gamemenu.h"

GameMenu::GameMenu(Player* player) 
: MenuWindow(), player(player)
{
	if (!gConfig.bFullScreen)
		window = guienv->addWindow(rect<s32>(iWidth/2-400,iHeight/2-260,iWidth/2+400,iHeight/2+260), true, L"Player Ship");
	else
		window = guienv->addWindow(rect<s32>(iWidth/2-575,iHeight/2-320,iWidth/2+575,iHeight/2+320), true, L"Player Ship");
	window->getCloseButton()->setVisible(false);
	window->setDrawBackground(false);

	tabs = guienv->addTabControl(rect<s32>(0,0,iWidth/2+800,iHeight/2+600), window, true);

	initializeDisplay();

	window->setVisible(false);
}

//virtual destructor called in some base
GameMenu::~GameMenu()
{
	delete ship;
}

void GameMenu::run()
{
	MenuWindow::run();
}

void GameMenu::initializeDisplay()
{
	ship = new ShipTab(tabs, player);
}
