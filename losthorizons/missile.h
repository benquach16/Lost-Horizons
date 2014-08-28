#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "projectile.h"
#include "targetableobject.h"


//we want cool looking shit
class Missile : public Projectile
{
public:
	static std::vector<Missile*> allMissiles;
	Missile(const u16 ID, const TargetableObject *target, const TurretProperties &turretProps, 
		const vector3df &position, 
		const vector3df &rotation);
	virtual ~Missile();
	virtual bool run();
	void damage(int damage);
	const TargetableObject *getCurrentTarget() const;
protected:
	int health;
	int index;
	void initMissile();
	scene::IParticleSystemSceneNode *exhaust;
	int missileTimer;
	//TODO:: replace target pointers with IDs
	const TargetableObject* target;
};

#endif
