#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ship.h"

class Player : public Ship
{
public:
	Player(const E_GAME_FACTION faction, const ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation);
	Player(const ShipInformation &info, const std::vector<s8> &subsystems, const vector3df &position, const vector3df &rotation);
	virtual ~Player();
	virtual bool run();
	virtual const E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const;

private:
	
};


#endif
