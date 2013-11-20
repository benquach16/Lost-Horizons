#include "stdafx.h"
#include "globals.h"
#include "missionmenu.h"

using namespace base;

MissionMenu::MissionMenu(gui::IGUIWindow *menu) :
	MenuWindow(guienv->addWindow(rect<s32>(width/2-300,height/2-200,width/2+300,height/2+200), true, 0, menu))
{

}

MissionMenu::~MissionMenu()
{
}
