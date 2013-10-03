#ifndef _TRIGGER_H_
#define _TRIGGER_H_

#include "irrlicht.h"


using namespace irr;
using namespace core;


//triggers are a level design mission element
//when an object enters the trigger area, we do another mission element
//such as complete objective or spawn enemy ships etc
class Trigger
{
public:
	Trigger(const vector3df& postion);
	~Trigger();
	void run();
protected:
	vector3df position;
};


#endif
