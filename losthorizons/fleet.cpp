#include "stdafx.h"
#include "fleet.h"
#include "ship.h"

Fleet::Fleet(E_FLEET_ROLE role) : fleetRole(role)
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
		//we should force them to follow their commands
	}
}

void Fleet::addShipToFleet(Ship *s)
{
	shipsInFleet.push_back(s);
	s->addToFleet(this);
}

void Fleet::removeShipFromFleet(Ship *s)
{
	//n time
	for(unsigned i = 0; i < shipsInFleet.size(); i++)
	{
		if(shipsInFleet[i] == s)
		{
			//flip
			shipsInFleet[i]->removeFromFleet();
			shipsInFleet[i] = shipsInFleet.back();
			shipsInFleet.pop_back();
			return;
		}
	}
}

bool Fleet::isShipInFleet(const Ship *s) const
{
	for(unsigned i = 0; i < shipsInFleet.size(); i++)
	{
		if(shipsInFleet[i] == s)
		{
			return true;
		}
	}
	return false;
}

const Ship* Fleet::getCommandingShip() const
{
	return shipsInFleet[0];
}
