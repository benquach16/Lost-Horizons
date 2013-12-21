#include "stdafx.h"
#include "globals.h"
#include "config.h"
#include "missionmenu.h"
#include <fstream>
using namespace base;

MissionMenu::MissionMenu() :
		MenuWindow(guienv->addWindow(rect<s32>(width/2-200,height/2-200,width/2+200,height/2+200), true)),
		missionList(0), accept(0), cancel(0), description(0)
{
	//initialize mission list
	window->setDraggable(false);
	window->getCloseButton()->setVisible(false);
	window->setDrawTitlebar(false);
	window->setVisible(false);
	missionList = guienv->addListBox(rect<s32>(20,20,200,360), window);
	accept = guienv->addButton(rect<s32>(220,20,320,40), window, -1, L"Accept");
	cancel = guienv->addButton(rect<s32>(220,60,320,80), window, -1, L"Cancel");
	//we'll put the description below the buttons
	description = guienv->addStaticText(L"", rect<s32>(220, 100, 380, 380), true, true, window);
		
}

MissionMenu::~MissionMenu()
{
}

void MissionMenu::getMissionList()
{
	//read in a specific file here
}

void MissionMenu::run()
{
	//do missionmenu stuff here
	MenuWindow::run();
	if(getVisible())
	{
		window->getParent()->getParent()->bringToFront(window->getParent());
		//for now just start the gaem when the player presses accept
		if(accept->isPressed())
		{
			gConfig.bPlay = true;
			game->createNewGame();
			setVisible(false);
		}
		if(cancel->isPressed())
		{
			gConfig.bPlay = false;
			setVisible(false);
		}
	}
}
