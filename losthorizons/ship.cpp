//#include "stdafx.h"
#include "ship.h"

std::list<Ship*> Ship::allShips;

Ship::Ship() : Object(0, vector3df(0,0,0), vector3df(0,0,0))
{
}

Ship::Ship(irr::IrrlichtDevice *graphics, const ShipProperties &props, const vector3df &position, const vector3df &rotation,
		   bool isPlayer) : 
	Object(graphics, props.getFilename().c_str(), position, rotation, props.getScale()), isPlayer(isPlayer)
{
	//add it to the ships list
	allShips.push_back(this);
	it = allShips.end();
}

Ship::~Ship()
{
	//destructor
	allShips.erase(it);
}

void Ship::run()
{
	if(hull > 0)
	{
		//make sure its alive to do anything
	}

}
