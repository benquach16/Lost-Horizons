#include "missionmanager.h"

MissionManager::MissionManager()
{
}

MissionManager::~MissionManager()
{
}

void MissionManager::run()
{
	for(unsigned i = 0; i < data.size(); i++)
	{
		//update all missions
		data[i].run();
	}
}

const std::vector<Mission>& MissionManager::getMissions() const
{
	return data;
}
