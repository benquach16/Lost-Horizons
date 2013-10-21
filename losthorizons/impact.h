#ifndef _IMPACT_H_
#define _IMPACT_H_

#include "effect.h"

//part of the sfx classes
//small impact effect that is caused from projectiles

class Impact : public Effect 
{
public:
	Impact(const core::vector3df& position);
	virtual ~Impact();
	virtual bool run();

protected:
	scene::IParticleSystemSceneNode *fireParticles;
	scene::IParticleSystemSceneNode *debrisParticles;
};

#endif
