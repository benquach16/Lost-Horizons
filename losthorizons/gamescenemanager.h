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
	GameSceneManager(irr::IrrlichtDevice *graphics, E_GAME_SCENE scene);
	~GameSceneManager();

	void runCurrentScene(f32 frameDeltaTime);
	void changeCurrentScene(E_GAME_SCENE scene);
	GameScene *getCurrentScene();

private:
	irr::IrrlichtDevice *graphics;
	GameScene *currentScene;
};

#endif
