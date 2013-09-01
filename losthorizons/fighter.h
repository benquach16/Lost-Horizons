#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include "targetableobject.h"

//fighter class
//they mostly provide something for point defense to kill
class Fighter : public TargetableObject
{
public:
	Fighter();
	virtual ~Fighter();
	virtual void run(f32 frameDeltaTime);
protected:

};

#endif
