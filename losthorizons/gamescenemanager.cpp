#include "stdafx.h"
#include "gamescenemanager.h"

GameSceneManager::GameSceneManager()
	: sceneType(SCENE_MAINMENU), scene(new GameScene), playerCam(new PlayerCamera)
{
}

GameSceneManager::~GameSceneManager()
{
	delete scene;
	delete playerCam;
}

void GameSceneManager::run()
{
	if (scene)
		scene->run();
}

void GameSceneManager::destroyScene()
{
	if (scene)
		delete scene;
	scene = 0;
}

void GameSceneManager::createScene()
{
	if (scene)
		delete scene;
	scene = new GameScene(sceneType);
}

void GameSceneManager::changeCurrentScene(E_GAME_SCENE newScene)
{
	sceneType = newScene;
}

E_GAME_SCENE GameSceneManager::getCurrentScene()
{
	return sceneType;
}

//functions for creating scene objects
PlayerCamera *GameSceneManager::createPlayerCam(const vector3df &position)
{
	delete playerCam;
	return playerCam = new PlayerCamera(position);
}

Ship *GameSceneManager::createShip(const E_GAME_FACTION &faction, const ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation)
{
	if (Ship::allShips.empty())
	{
		Player *p = new Player(faction, shipType, position, rotation);
		return p->getShip();
	}
	else
		return new Ship(faction, shipType, position, rotation);
}

Ship *GameSceneManager::createShip(u16 ID, const ShipInformation &info, const s8 *subsystems, const vector3df &position, const vector3df &rotation)
{
	if (Ship::allShips.empty())
	{
		Player *p = new Player(info, subsystems, position, rotation);
		return p->getShip();
	}
	else
		return new Ship(ID, info, subsystems, position, rotation);
}

SpaceStation *GameSceneManager::createStation(const E_GAME_FACTION faction, const ObjectManager::E_STATION_LIST stationType, const vector3df &position,
									   const vector3df& rotation)
{
	return new SpaceStation(faction, stationType, position, rotation);
}

PlayerCamera *GameSceneManager::getCamera()
{
	return playerCam;
}
