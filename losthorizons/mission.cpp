#include "stdafx.h"
#include "mission.h"

Mission::Mission()
{
	//randomly generate mission
	
}

Mission::Mission(const MissionProperties& missionInfo) : 
	name(missionInfo.getName()), description(missionInfo.getDesc())
{
	//create ships from missioninfo here 
	//because we don't want to load as we parse the file
	std::queue<shipCreateQueue> q;
	q = missionInfo.getCreationQueue();
	while(!q.empty())
	{
		//should use actual create functions
		shipCreateQueue st = q.front();
		Ship *s = new Ship(st.faction, (ObjectManager::E_SHIP_LIST)st.shipType,
											 st.position, st.rotation);
		q.pop();
	}

	for(unsigned i = 0; i < missionInfo.getObjs().size(); i++)
	{
		//make sure we reallocate here
		//make sure we start with derived class!!!!!!
		//do not use base class constructor!!!!
		//objectives.push_back(new Objective(*missionInfo.getObjs()[i]));
	}
}

Mission::~Mission()
{
	for(unsigned i = 0; i < objectives.size(); i++)
	{
		delete objectives[i];
	}
}

bool Mission::run()
{
	if(objectives.size() > 0)
	{
		//make sure we still have objectives to run
		if(objectives[0]->run())
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
		return objectives[0]->getPosition();
	return vector3df();
}
