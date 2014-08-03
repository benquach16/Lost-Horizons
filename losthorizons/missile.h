#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "projectile.h"

//we want cool looking shit
class Missile : public Projectile
{
public:
	static std::vector<Missile*> allMissiles;
	Missile();
	virtual ~Missile();
	virtual bool run();

protected:
	TargetableObject* target;
};

#endif
