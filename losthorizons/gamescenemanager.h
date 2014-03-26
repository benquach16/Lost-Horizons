#ifndef _GAMESCENEMANAGER_H_
#define _GAMESCENEMANAGER_H_

#include "gamescene.h"
#include "playercamera.h"
#include "player.h"
#include "spacestation.h"

class GameSceneManager
{
public:
	GameSceneManager();
	~GameSceneManager();

	void run();
	void destroyScene();
	void createScene();
	void changeCurrentScene(E_GAME_SCENE newScene);
	E_GAME_SCENE getCurrentScene();
	PlayerCamera *getCamera();

	PlayerCamera *createPlayerCam(const vector3df &position = vector3df(0.f));
	Ship *createShip(const E_GAME_FACTION &faction, const ObjectManager::E_SHIP_LIST shipType = ObjectManager::E_SHIP_LIST::PRAE_CRUISER,
					 const vector3df &position = vector3df(0.f), const vector3df &rotation = vector3df(0.f));
	Ship *createShip(const u16 ID, const ShipInformation &info, const s8 *subsystems,
					 const vector3df &position, const vector3df &rotation);
	SpaceStation *createStation(const E_GAME_FACTION faction,
								const ObjectManager::E_STATION_LIST stationType = ObjectManager::E_STATION_LIST::TRADING,
								const vector3df &position = vector3df(0.f), const vector3df& rotation = vector3df(0.f));

private:
	E_GAME_SCENE sceneType;
	GameScene *scene;
	PlayerCamera *playerCam;
};

#endif
