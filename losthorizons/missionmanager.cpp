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
	while (i < data.size()) {
		if (data[i].run())
			i++;
		else {
			if (intercom) {
				intercom->postMessage(L"Mission complete sir");
			}
			data[i] = data.back();
			data.pop_back();
		}
	}
}

void MissionManager::addMission(const MissionProperties& missionInfo)
{
	data.push_back(Mission(missionInfo));
}

const std::vector<Mission>& MissionManager::getMissions() const
{
	return data;
}
