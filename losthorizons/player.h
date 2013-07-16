#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ship.h"

class Player : public Ship
{
public:
	//default constructor
	Player();
	//parameterized constructor
	Player(const ShipProperties &props, const vector3df &position, const vector3df &rotation);
	virtual ~Player();
	virtual void run(f32 frameDeltaTime);

protected:

};


#endif
