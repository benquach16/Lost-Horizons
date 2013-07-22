#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include <list>
#include <vector>

#include "turretproperties.h"
#include "object.h"

//basic projectile class
class Projectile : public Object
{
public:
	static std::list<Projectile*> allProjectiles;

	//initialize with position, rotation, and information
	Projectile(const vector3df &position, const vector3df &rotation, const TurretProperties &turretProps);
	~Projectile();

	//does everything a projectile is supposed to
	void run(f32 frameDeltaTime);

protected:
	void movement(f32 frameDeltaTime);
	bool checkIfOutOfRange();
	core::vector3df originalPosition;
	int range;
	int velocity;

	//iterator to this
	std::list<Projectile*>::iterator it;
};

#endif