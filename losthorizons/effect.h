#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <vector>
#include <list>

#include "irrlicht.h"


//define a special effects base class right here
//so we can control when and where special effects happen and when to end them

class Effect
{
public:
	Effect();
	virtual ~Effect();
	virtual void run();

	static std::vector<Effect*> allEffects;
protected:

};

#endif
