#ifndef _TURNINGMARKER_H_
#define _TURNINGMARKER_H_

#include "player.h"

//object designed to give pplayer more control over ship navigation
class TurningMarker
{
public:
	TurningMarker(Player *player);
	virtual ~TurningMarker();
	virtual void run();

protected:
	//protected function
	//does exactly what it says
	void setVisible(bool visible);
	//need player information so we can orient this correctly
	Player* player;
	//consists of 3 objects
	scene::ISceneNode *XYcircle;
	scene::ISceneNode *YZcircle;
	scene::IMeshSceneNode *arrow;
};

#endif
