#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "irrlicht.h"


//define a special effects base class right here
//so we can control when and where special effects happen and when to end them

class Effect
{
public:
	Effect(int lengthInMilliseconds);
	virtual ~Effect();
	virtual bool run();

	static std::vector<Effect*> allEffects;
protected:
	//the length of the effect before we delete it
	int lengthInMilliseconds;
	unsigned totalTime;
};

#endif
