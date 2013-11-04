#include "stdafx.h"
#include "missionmanager.h"

MissionManager::MissionManager() 
	
{

}

MissionManager::~MissionManager()
{
}

void MissionManager::run(Intercom *intercom)
{
	//update all missions
	unsigned i = 0;
	while (i < missionList.size()) {
		if (missionList[i].run())
			i++;
		else {
			if (intercom) {
				intercom->postMessage(L"Mission complete sir");
			}
			missionList[i] = missionList.back();
			missionList.pop_back();
		}
	}
}

void MissionManager::addMission(const MissionProperties& missionInfo)
{
	missionList.push_back(Mission(missionInfo));
}

const std::vector<Mission>& MissionManager::getMissions() const
{
	return missionList;
}
