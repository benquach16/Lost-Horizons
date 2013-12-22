#ifndef _FLEET_H_
#define _FLEET_H_

#include "ship.h"

//'fleets' are meant to group multiple ships together
//and make them do stuff
class Fleet
{
public:
	Fleet();
	~Fleet();
private:
	//so we got an initial problem here, which is double pointers
	//ship needs to tell its fleet that it fuckin lost
	std::vector<Ship*> shipsInFleet;
};


#endif
