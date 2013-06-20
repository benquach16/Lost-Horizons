#ifndef _SHIP_H_
#define _SHIP_H_

#include <list>
#include <string>
#include "object.h"
#include "shipproperties.h"


class Ship : public Object
{
public:
	//contain the list inside ship class so all ships can access any other ship if needed
	static std::list<Ship*> allShips;

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
	int hull, armor, shield;
	int maxHull, maxArmor, maxShield;

	int velocity;
	int maxVelocity;

	int maxTurn;

	//other stats
	Ship *shipTarget;
};
#endif
