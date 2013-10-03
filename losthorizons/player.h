#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ship.h"

class Player : public Ship
{
public:
	Player(E_GAME_FACTION faction, ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation);
	Player(const ShipInformation &info, const vector3df &position, const vector3df &rotation);
	virtual ~Player();
	virtual void run(f32 frameDeltaTime);
	virtual const E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const;

private:
	
};


#endif
