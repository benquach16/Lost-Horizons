#include "stdafx.h"
#include "globals.h"
#include "gotoobjective.h"

using namespace base;

const int OBJECTIVE_CHECK_TIMER = 500;

GotoObjective::GotoObjective(const std::wstring &description, const irr::core::vector3df& position) : 
	Objective(description, position)
{
}


GotoObjective::GotoObjective(const irr::core::vector3df& position) : 
	Objective(L"Go To Objective", position)
{
}

GotoObjective::~GotoObjective()
{
}

bool GotoObjective::run()
{
	//check if the player is close enough to objective
	if(timeKeeping < timer->getTime())
	{
		if(Ship::allShips[0]->getPosition().getDistanceFromSQ(position) < 25000)
		{
			return true;
		}
		timeKeeping = timer->getTime() + OBJECTIVE_CHECK_TIMER;
	}
	return false;
}

const E_OBJECTIVE_TYPE GotoObjective::getObjectiveType() const
{
	return OBJECTIVE_GOTO;
}
