#ifndef _SHIP_H_
#define _SHIP_H_

#include <list>
#include "targetableobject.h"

struct ShipTypes
{
	//define the stats of each ship
	//hp, turret slots, etc etc
	int hull;
};


class Ship : public TargetableObject
{
public:
	Ship();
	//copy constructor
	Ship(const Ship &s);
	//overloaded assignment operator
	Ship& operator=(const Ship &s);
	~Ship();

	virtual void run();


private:
	//iterator to 'this'
	std::list<Ship*>::iterator it;

	//stats
	//basic ship type
	ShipTypes shipType;
	int hull, armor, shield;
	int velocity;

	//other stats
	Ship *shipTarget;
};

//contain the list inside ship class so all ships can access any other ship if needed
static std::list<Ship*> allShips;

#endif
