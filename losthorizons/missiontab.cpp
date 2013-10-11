#include "stdafx.h"
#include "missiontab.h"

MissionTab::MissionTab(gui::IGUITabControl *tabs) : MenuTab(), missionList(0), missionDescription(0)
{
	tab = tabs->addTab(L"Mission Log");

	missionList = guienv->addListBox(rect<s32>(20, 20, 300, 480), tab);
	missionDescription = guienv->addStaticText(L"", rect<s32>(320, 20, 780, 480), false, true, tab);
}

MissionTab::~MissionTab()
{
}
