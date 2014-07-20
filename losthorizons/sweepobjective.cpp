#include "stdafx.h"
#include "sweepobjective.h"

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
	
	return false;
}

const E_OBJECTIVE_TYPE SweepObjective::getObjectiveType() const
{
	return OBJECTIVE_SWEEP;
}
