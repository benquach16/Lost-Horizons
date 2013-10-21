#ifndef _TRIGGER_H_
#define _TRIGGER_H_

#include "stdafx.h"

using namespace irr;

//triggers are a level design mission element
//when an object enters the trigger area, we do another mission element
//such as complete objective or spawn enemy ships etc
class Trigger
{
public:
	Trigger(const core::vector3df& postion);
	~Trigger();
	void run();
protected:
	core::vector3df position;
};


#endif
