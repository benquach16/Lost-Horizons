#include "stdafx.h"
#include "sweepobjective.h"
#include "globals.h"

using namespace base;

const int OBJECTIVE_CHECK_TIMER = 500;

SweepObjective::SweepObjective(const std::wstring& description,
							   const vector3df& position) : 
Objective(description, position)
{

}

SweepObjective::SweepObjective(const vector3df& position) :
	Objective(L"Sweep Objective", position)
{

}

SweepObjective::~SweepObjective()
{
}

bool SweepObjective::run()
{
	//make sure we dont poll every frame for fps
	if(timeKeeping < timer->getTime())
	{
		
		for(unsigned i = 0; i < Ship::allShips.size(); i++)
		{
			if(Ship::allShips[i]->getPosition().getDistanceFromSQ(position) < 25000000 && Ship::allShips[i]->getFaction() == FACTION_PIRATE)
			{
				return false;
			}
		}
		timeKeeping = timer->getTime() + OBJECTIVE_CHECK_TIMER;
	}
	return true;
}

const E_OBJECTIVE_TYPE SweepObjective::getObjectiveType() const
{
	return OBJECTIVE_SWEEP;
}
