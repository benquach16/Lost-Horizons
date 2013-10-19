#ifndef _MARKER_H_
#define _MARKER_H_

#include "object.h"

//marker that has some special effects
class Marker : public Object
{
public:
	Marker();
	
	virtual void run(f32 frameDeltaTime);

protected:

};

#endif
