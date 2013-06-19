#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

//Here we manage the current scene and all objects inside of the scene
//We shouldn't deal with creating multiple scenes too much, since an entire solar system should be a single scene
//only for the implementation of multiple solar systems
//so for now, keep the design as a singleton
#include <list>

#include "player.h"

class GameScene
{
public:
	GameScene();
	//parameterized constructor
	GameScene(IrrlichtDevice *graphics);
	~GameScene();
	void loadScene();
	void saveScene();

	void run();
private:
	IrrlichtDevice *graphics;

};

#endif
