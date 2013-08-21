#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "effect.h"

using namespace irr;
using namespace scene;


//explosion class
class Explosion : public Effect
{
public:
	Explosion();
	~Explosion();
	virtual bool run();

protected:
	scene::IParticleSystemSceneNode *fireParticles;

};

#endif
