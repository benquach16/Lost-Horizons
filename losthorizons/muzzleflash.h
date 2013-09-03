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
	Muzzleflash(const IBoneSceneNode *parent);
	~Muzzleflash();
	virtual bool run();
protected:
	//we parent the effect to a joint so it doesnt lag
	const IBoneSceneNode *parent;
};

#endif
