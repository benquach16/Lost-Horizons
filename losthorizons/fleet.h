#ifndef _FLEET_H_
#define _FLEET_H_

#include <vector>
#include "irrlicht.h"

using namespace irr;
using namespace core;

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
	Fleet();
	~Fleet();
	//loop through all the ships in the fleet and make them do stuff
	void run();
	void addShipToFleet(Ship *s);
	void removeShipFromFleet(Ship *s);
	//fleet orders, applies to every ship
	void moveToPosition(const vector3df &position);
	void attackTarget(Ship *target);
private:
	//so we got an initial problem here, which is double pointers
	//ship needs to tell its fleet that it fuckin lost
	std::vector<Ship*> shipsInFleet;
	//index 0 is fleet leader - all ships follow
};


#endif
