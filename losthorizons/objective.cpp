#include "objective.h"

Objective::Objective(const std::wstring &desciption, E_OBJECTIVE_TYPES objectiveType, const vector3df& position, const unsigned radius) : 
	description(description), objectiveType(objectiveType), position(position), radius(radius)
{

}

Objective::~Objective()
{
}

bool Objective::run()
{
	if(objectiveType == E_OBJECTIVETYPE_SWEEP)
	{
		//we check for ships around sweep area
	}
	return false;
}
