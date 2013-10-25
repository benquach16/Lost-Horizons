#include "stdafx.h"
#include "savemenu.h"
#include "globals.h"
#include "datamanager.h"

using namespace base;

SaveMenu::SaveMenu(gui::IGUIWindow *menu)
	: MenuWindow(guienv->addWindow(rect<s32>(width/2-300,height/2-200,width/2+300,height/2+200), true, 0, menu))
{

}

SaveMenu::~SaveMenu()
{
}
