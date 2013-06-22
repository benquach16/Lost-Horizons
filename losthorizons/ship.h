#ifndef _SHIP_H_
#define _SHIP_H_

#include <list>
#include <string>
#include "object.h"
#include "shipproperties.h"

//for finite state machine implementation
enum E_AI_STATES
{
	STATE_PATROLLING,
	STATE_FLEEING,
	STATE_ATTACKING,
	STATE_DEFENDING,
	STATE_ASSAULTING
};

//basic ship class
class Ship : public Object
{
public:
	//contain the list inside ship class so all ships can access any other ship if needed
	static std::list<Ship*> allShips;

	Ship();
	Ship(irr::IrrlichtDevice *graphics, const ShipProperties &props,
		const vector3df &position, const vector3df &rotation, bool isPlayer);
	//copy constructor
	Ship(const Ship &s);
	//overloaded assignment operator
	Ship& operator=(const Ship &s);
	~Ship();

	virtual void run();

protected:
	bool isPlayer;
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
