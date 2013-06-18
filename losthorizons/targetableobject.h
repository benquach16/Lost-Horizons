#ifndef _TARGETABLEOBJECT_H_
#define _TARGETABLEOBJECT_H_

//This is the class of all renderable objects that are able to be selected by the player

#include "object.h"

class TargetableObject : public Object
{
public:
	TargetableObject();
	~TargetableObject();

	virtual void run();
private:

};

#endif
