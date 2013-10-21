#ifndef _MUZZLEFLASH_H_
#define _MUZZLEFLASH_H_

#include "effect.h"

//muzzleflash effect class
class Muzzleflash : public Effect
{
public:
	//public funcs
	Muzzleflash(scene::IBoneSceneNode *parent, const core::vector3df &rotation);
	virtual ~Muzzleflash();
	virtual bool run();

protected:
	//we parent the effect to a joint so it doesnt lag
	scene::IBoneSceneNode *parent;
	//scene::IAnimatedMeshSceneNode *mesh;
	scene::IParticleSystemSceneNode *particle;
};

#endif
