#include "stdafx.h"
#include "objective.h"
#include <iostream>

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
		for (unsigned i = 0; i < Ship::allShips.size(); i++)
		{
			if (Ship::allShips[i]->getPosition().getDistanceFromSQ(position) < (radius * radius) &&
				Ship::allShips[0]->getFaction() != Ship::allShips[i]->getFaction())
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

const vector3df& Objective::getPosition() const
{
	return position;
}
