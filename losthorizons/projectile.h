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
	Projectile(u16 ID, const TurretProperties &turretProps, const vector3df &position, const vector3df &rotation);
	~Projectile();

	//does everything a projectile is supposed to
	void run(f32 frameDeltaTime);

protected:
	void movement(f32 frameDeltaTime);
	bool checkIfOutOfRange();

	core::vector3df originalPosition;
	u16 ID;
	int damage;
	int range;
	int velocity;

private:
	//iterator to this
	unsigned index;
};

#endif
