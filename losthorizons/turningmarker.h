#ifndef _TURNINGMARKER_H_
#define _TURNINGMARKER_H_

#include "stdafx.h"

using namespace irr;

//object designed to give pplayer more control over ship navigation
class TurningMarker
{
public:
	TurningMarker();
	virtual ~TurningMarker();
	virtual void run(const core::vector3df &pos, const core::vector3df &rot, const core::vector3df &targetRot);

protected:
	//protected function
	//does exactly what it says
	void setVisible(bool visible);
	//consists of 3 objects
	scene::ISceneNode *XYcircle;
	scene::ISceneNode *YZcircle;
	scene::IMeshSceneNode *arrow;
};

#endif
