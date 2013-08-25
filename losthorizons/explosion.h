#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "effect.h"

using namespace irr;
using namespace scene;
using namespace core;

//explosion class
class Explosion : public Effect
{
public:
	Explosion(const vector3df& position);
	~Explosion();
	virtual bool run();

protected:
	scene::IParticleSystemSceneNode *fireParticles;
	scene::ISceneNode *shockwave;
};

#endif
