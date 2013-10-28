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
	for(unsigned i = 0; i < data.size(); i++)
	{
		//update all missions
		if(data[i].run())
		{
			
			i++;
		}
		else
		{
			if(intercom)
			{
				intercom->addText(L"Mission complete sir");
			}
			data[i] = data.back();
			data.pop_back();
			i--;
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
