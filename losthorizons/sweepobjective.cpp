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
	Objective(position)
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
		
	}
	return false;
}

const E_OBJECTIVE_TYPE SweepObjective::getObjectiveType() const
{
	return OBJECTIVE_SWEEP;
}
