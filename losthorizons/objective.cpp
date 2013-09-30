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
		unsigned counter = 0;
		for (std::list<Ship*>::iterator i = Ship::allShips.begin(); i != Ship::allShips.end(); ++i)
		{
			if ((*i)->getPosition().getDistanceFromSQ(position) < (radius * radius) &&
				(*Ship::allShips.begin())->getFaction() != (*i)->getFaction())
			{
				counter++;
			}
		}
		if(!counter)
		{
			//return true if we finished the objective
			return true;
		}
	}
	return false;
}
