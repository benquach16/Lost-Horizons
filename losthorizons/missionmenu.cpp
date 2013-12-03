#include "stdafx.h"
#include "globals.h"
#include "missionmenu.h"

using namespace base;

MissionMenu::MissionMenu(gui::IGUIWindow *menu) :
		MenuWindow(guienv->addWindow(rect<s32>(width/2-300,height/2-200,width/2+300,height/2+200), true, 0, menu)),
		missionList(0), accept(0), cancel(0)
{
		//initialize mission list
		missionList = guienv->addListBox(rect<s32>(20,20,200,360), window);
		
}

MissionMenu::~MissionMenu()
{
}

void MissionMenu::run()
{
		//do missionmenu stuff here
}
