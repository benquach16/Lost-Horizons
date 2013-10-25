#include "stdafx.h"
#include "effect.h"
#include "globals.h"

using namespace base;

std::vector<Effect*> Effect::allEffects;

//constructor
Effect::Effect(int milliseconds) : endTime(timer->getTime() + milliseconds)
{
	allEffects.push_back(this);
}

Effect::~Effect()
{
}

bool Effect::run()
{
	//check if the effect has run out of time
	return timer->getTime() < endTime;
}
