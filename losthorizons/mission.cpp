#include "stdafx.h"
#include "mission.h"

Mission::Mission()
{
	//randomly generate mission
	
}

Mission::Mission(const MissionProperties& missionInfo) : 
	name(missionInfo.getName()), description(missionInfo.getDesc()),
	objectives(missionInfo.getObjs())
{
	//create ships from missioninfo here 
	//because we don't want to load as we parse the file
	std::queue<shipCreateQueue> queue;
	queue = missionInfo.getCreationQueue();
	while(!queue.empty())
		{
			
		}
}

Mission::~Mission()
{
}

bool Mission::run()
{
	if(objectives.size() > 0)
	{
		//make sure we still have objectives to run
		if(objectives[0].run())
		{
			//objective completed
			objectives.erase(objectives.begin());
		}
	}
	return objectives.size() > 0;
}

const wchar_t *Mission::getName() const
{
	return name.c_str();
}

const wchar_t *Mission::getDesc() const
{
	return description.c_str();
}

const vector3df Mission::getCurrObjPos() const
{
	if(objectives.size())
		return objectives[0].getPosition();
	return vector3df();
}
