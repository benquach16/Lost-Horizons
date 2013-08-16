#ifndef _TURNINGMARKER_H_
#define _TURNINGMARKER_H_

#include "object.h"
#include "player.h"
//object designed to give pplayer more control over ship navigation
class TurningMarker
{
public:
	TurningMarker(Player *player);
	virtual ~TurningMarker();
	virtual void run();

protected:
	//need player information so we can orient this correctly
	Player* player;
	//consists of 3 objects
	Object *XYcircle;
	Object *YZcircle;
	Object *arrow;
};

#endif
