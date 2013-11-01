#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "turretproperties.h"
#include "object.h"
#include "impact.h"
#include "explosion.h"

//basic projectile class
class Projectile : public Object
{
public:
	static std::vector<Projectile*> allProjectiles;

	//initialize with position, rotation, and information
	Projectile(const u16 ID, const TurretProperties &turretProps, const vector3df &position, const vector3df &rotation);
	~Projectile();

	//does everything a projectile is supposed to
	bool run();

protected:
	void movement();
	bool inRange();

	core::vector3df originalPosition;
	u16 ID;
	int damage;
	int range;
	int velocity;

	//iterator to this
	unsigned index;
};

#endif
