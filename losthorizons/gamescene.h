#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

//Here we manage the current scene and all objects inside of the scene
//We shouldn't deal with creating multiple scenes too much, since an entire solar system should be a single scene
//only for the implementation of multiple solar systems
//so for now, keep the design as a singleton
#include "stdafx.h"
#include "object.h"
#include <stack>

using namespace irr;
using namespace scene;

enum E_GAME_SCENE
{
	SCENE_MAINMENU,
	SCENE_TAU_CETI,
};

class GameScene
{
public:
	GameScene(E_GAME_SCENE scene = SCENE_MAINMENU);
	~GameScene();
	//void loadScene();
	//void saveScene();
	void run();

private:
	ISceneNode *skybox;
	std::stack<ISceneNode*> sceneObjects;		//stores static scene node objects
	std::stack<Object*> dynamicObjects;			//stores the stuff with more complexity

	
};

#endif
