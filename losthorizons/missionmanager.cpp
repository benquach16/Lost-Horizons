#include "stdafx.h"
#include "missionmanager.h"

MissionManager::MissionManager() 
	
{
	
}

MissionManager::~MissionManager()
{
	for(unsigned i = 0; i < missionList.size(); i++)
	{
		delete missionList[i];
	}
}

void MissionManager::run(Intercom *intercom)
{
	//update all missions
	unsigned i = 0;
	while (i < missionList.size()) 
	{
		if (missionList[i]->run())
		{
			i++;
		}
		else 
		{
			intercom->postMessage(L"Mission complete sir");
			missionList[i] = missionList.back();
			missionList.pop_back();
		}
	}
}

void MissionManager::addMission(const MissionProperties& missionInfo)
{
	//Problem here:
	//this creates not one but two missions
	//and the waay that missions work is that they have the objective pointers vector
	//so we havae to make it make only 1 mission
	missionList.push_back(new Mission(missionInfo));
}

const std::vector<Mission*>& MissionManager::getMissions() const
{
	return missionList;
}
