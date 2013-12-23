#include "stdafx.h"
#include "fleet.h"

Fleet::Fleet()
{
	
}

Fleet::~Fleet()
{
	//dont clear memory!!!
}

void Fleet::run()
{
	for(unsigned i = 0; i < shipsInFleet.size(); i++)
	{
		//do fleetstuff
		//tell them to do shit
	}
}

void Fleet::addShipToFleet(Ship *s)
{
	shipsInFleet.push_back(s);
}

void Fleet::removeShipFromFleet(Ship *s)
{
	//n time
	for(unsigned i = 0; i < shipsInFleet.size(); i++)
	{
		if(shipsInFleet[i] == s)
		{
			//flip
			shipsInFleet[i] = shipsInFleet.back();
			shipsInFleet.pop_back();
			return;
		}
	}
}
