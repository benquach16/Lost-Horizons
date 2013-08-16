#ifndef _TURNINGMARKER_H_
#define _TURNINGMARKER_H_

#include "object.h"
//object designed to give pplayer more control over ship navigation
class TurningMarker : public Object
{
public:
	TurningMarker();
	virtual ~TurningMarker();
	virtual void run();
};

#endif
