#ifndef _MUZZLEFLASH_H_
#define _MUZZLEFLASH_H_

#include "effect.h"

using namespace irr;
using namespace scene;
using namespace core;

//muzzleflash effect class
class Muzzleflash : public Effect
{
public:
	//public funcs
	Muzzleflash(IBoneSceneNode *parent, const vector3df &rotation);
	virtual ~Muzzleflash();
	virtual bool run();
protected:
	//we parent the effect to a joint so it doesnt lag
	IBoneSceneNode *parent;
	scene::IAnimatedMeshSceneNode *mesh;
};

#endif
