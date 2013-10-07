#ifndef _VISUALSMANAGER_H_
#define _VISUALSMANAGER_H_

#include <vector>

#include "irrlicht.h"

//the visuals manager has a very simple job - to make the game look cool
//it simply controls the dust and nebula fog in space

class VisualsManager
{
public:
	VisualsManager();
	~VisualsManager();
	void run();

protected:
	scene::ICameraSceneNode *cam;
	std::vector<irr::scene::IBillboardSceneNode*> dust;
};

#endif
