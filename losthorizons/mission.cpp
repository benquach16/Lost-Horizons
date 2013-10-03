#include "mission.h"

Mission::Mission()
{
	//randomly generate mission
	
}

Mission::Mission(const MissionProperties& missionInfo)
{
}

Mission::~Mission()
{
}

void Mission::run()
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
	else
	{
		//mission complete
	}
}
