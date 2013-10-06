#ifndef _GAMESCENEMANAGER_H_
#define _GAMESCENEMANAGER_H_

#include "gamescene.h"

class GameSceneManager
{
public:
	GameSceneManager(irr::IrrlichtDevice *graphics, E_GAME_SCENE scene = SCENE_MAINMENU);
	~GameSceneManager();

	void runCurrentScene(f32 frameDeltaTime);
	void changeCurrentScene(E_GAME_SCENE scene);
	GameScene *getCurrentScene();

private:
	irr::IrrlichtDevice *graphics;
	GameScene *currentScene;
};

#endif
