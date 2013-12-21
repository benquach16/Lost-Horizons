#ifndef _FLEET_H_
#define _FLEET_H_

#include "ship.h"

//'fleets' are meant to group multiple ships together
//and make them do stuff
class Fleet
{
public:
	Fleet();

private:
	//so we got an initial problem here, which is double pointers
	vector<Ship*> shipsInFleet;
};


#endif
