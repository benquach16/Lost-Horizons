#ifndef _GAMESCENEMANAGER_H_
#define _GAMESCENEMANAGER_H_

#include "gamescene.h"

class GameSceneManager
{
public:
	//default constructor
	GameSceneManager();
	//parameterized constructors
	GameSceneManager(irr::IrrlichtDevice *graphics);
	GameSceneManager(irr::IrrlichtDevice *graphics, E_GAMESCENES scene);
	~GameSceneManager();

	void runCurrentScene(float frameDeltaTime);
	void changeCurrentScene(E_GAMESCENES scene);
	GameScene *getCurrentScene();

private:
	irr::IrrlichtDevice *graphics;
	GameScene *currentScene;
};

#endif
