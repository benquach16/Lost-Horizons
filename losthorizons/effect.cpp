#include "stdafx.h"
#include "effect.h"

std::vector<Effect*> Effect::allEffects;

Effect::Effect(int lengthInMilliseconds) : lengthInMilliseconds(lengthInMilliseconds), totalTime(timer->getTime() + lengthInMilliseconds)
{
	allEffects.push_back(this);
	it = allEffects.end();
}

Effect::~Effect()
{
	allEffects.erase(it);
}

void Effect::run()
{
	//check if the effect has run out of time
	if(totalTime < timer->getTime())
	{
		//delete the effect now
		delete this;
	}
}
