#ifndef _IMPACT_H_
#define _IMPACT_H_

#include "effect.h"

//part of the sfx classes
//small impact effect that is caused from projectiles

using namespace irr;
using namespace scene;

class Impact : public Effect 
{
public:
	Impact(const vector3df& position);
	virtual ~Impact();
	virtual void run();

protected:
	scene::IParticleSystemSceneNode *fireParticles;

};

#endif
