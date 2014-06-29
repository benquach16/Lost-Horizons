#ifndef _FLEET_H_
#define _FLEET_H_

#include <vector>
#include "irrlicht.h"

using namespace irr;
using namespace core;

enum E_FLEET_ROLE
{
	FLEET_ATTACKING,
	FLEET_PATROLLING,
	FLEET_DEFENDING,
	FLEET_PASSIVE
};


//we cant really have them include each other
//so we'll just do this workaroudn
class Ship;
//'fleets' are meant to group multiple ships together
//and make them do stuff
class Fleet
{
public:
	//slight problem is that its alot easier if fleets and ships could include
	//each toerh but that aint happenin
	Fleet(E_FLEET_ROLE role = FLEET_PATROLLING);
	~Fleet();
	//loop through all the ships in the fleet and make them do stuff
	void run();
	void addShipToFleet(Ship *s);
	void removeShipFromFleet(Ship *s);
	bool isShipInFleet(const Ship *s) const;
	//fleet orders, applies to every ship
	void moveToPosition(const vector3df &position);
	void attackTarget(const Ship *target);
	
	//some simple getters
	const Ship* getCommandingShip() const;
	const std::vector<Ship*> getShipsInFleet() const;
private:
	//so we got an initial problem here, which is double pointers
	//ship needs to tell its fleet that it fuckin lost
	std::vector<Ship*> shipsInFleet;
	//index 0 is fleet leader - all ships follow
	//fleetrole is really meant to be more of an AI thing
	E_FLEET_ROLE fleetRole;
};


#endif
