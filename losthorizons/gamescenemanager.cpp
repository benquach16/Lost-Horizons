#include "stdafx.h"
#include "gamescenemanager.h"

GameSceneManager::GameSceneManager(irr::IrrlichtDevice *graphics, E_GAME_SCENE scene)
	: graphics(graphics), currentScene(new GameScene(graphics, scene))
{
}

GameSceneManager::~GameSceneManager()
{
	delete currentScene;
}

void GameSceneManager::runCurrentScene(f32 frameDeltaTime)
{
	if (currentScene)
		currentScene->run(frameDeltaTime);
}

void GameSceneManager::changeCurrentScene(E_GAME_SCENE scene)
{
	//need to delete the entire scene
	if (currentScene)
		delete currentScene;
	currentScene = new GameScene(graphics, scene);
}

GameScene *GameSceneManager::getCurrentScene()
{
	return currentScene;
}
