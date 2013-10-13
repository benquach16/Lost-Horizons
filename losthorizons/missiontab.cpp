#include "stdafx.h"
#include "missiontab.h"

MissionTab::MissionTab(gui::IGUITabControl *tabs, MissionManager *missionManager) : MenuTab(), missionList(0), missionDescription(0),
	missionManager(missionManager)
{
	tab = tabs->addTab(L"Mission Log");

	missionList = guienv->addListBox(rect<s32>(20, 20, 300, 480), tab);
	missionDescription = guienv->addStaticText(L"", rect<s32>(320, 20, 780, 480), false, true, tab);
}

MissionTab::~MissionTab()
{
}

void MissionTab::run()
{
	loadMissions();
}

void MissionTab::loadMissions()
{
	//load missions from mission manager
	if(!missionList->getItemCount())
	{
		for(unsigned i = 0; i < missionManager->getMissions().size(); i++)
		{
			missionList->addItem(missionManager->getMissions()[i].getName().c_str());
		}
	}
}
