#include "objective.h"

Objective::Objective(const std::wstring &desciption, const E_OBJECTIVE_TYPE type, const vector3df& position, const unsigned radius) : 
	description(description), type(type), position(position), radius(radius)
{

}

Objective::Objective(const E_OBJECTIVE_TYPE type, const vector3df& position, const unsigned radius) : 
	type(type), position(position), radius(radius)
{
}

Objective::~Objective()
{
}

bool Objective::run()
{
	if(type == OBJECTIVE_SWEEP)
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
