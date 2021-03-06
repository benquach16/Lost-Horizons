#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "stdafx.h"
#include <vector>

using namespace irr;

//define a special effects base class right here
//so we can control when and where special effects happen and when to end them

class Effect
{
public:
	static std::vector<Effect*> allEffects;

	Effect(int milliseconds);
	virtual ~Effect();
	virtual bool run();

protected:
	//the length of the effect before we delete it
	unsigned endTime;
};

#endif
