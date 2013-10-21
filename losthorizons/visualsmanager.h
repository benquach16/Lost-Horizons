#ifndef _VISUALSMANAGER_H_
#define _VISUALSMANAGER_H_

#include "stdafx.h"
#include <vector>

//the visuals manager has a very simple job - to make the game look cool
//it simply controls the dust and nebula fog in space

class VisualsManager
{
public:
	VisualsManager();
	~VisualsManager();
	void run();

protected:
	irr::scene::ICameraSceneNode *cam;
	std::vector<irr::scene::IBillboardSceneNode*> dust;
};

#endif
