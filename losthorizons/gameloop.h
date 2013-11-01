#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

#include "player.h"
#include "fighter.h"
#include "gamescene.h"
#include "datamanager.h"
#include "gamescenemanager.h"
#include "objectmanager.h"
#include "visualsmanager.h"
#include "missionmanager.h"
#include "hud.h"
#include "intercom.h"
#include "turningmarker.h"
#include "stationmenu.h"
#include "gamemenu.h"
#include "cargo.h"

class Gameloop
{
public:
	Gameloop(DataManager *data);
	~Gameloop();
	void init();
	void run();

	//newgame or loadgame instances
	void createNewGame();
	void createLoadedGame(const std::string &filename);

	//functions for managing the scene
	GameSceneManager *getGameSceneManager() { return gameSceneManager; } const
	void setPlayer(Player* newPlayer) { player = newPlayer; }

private:
	void playerControl();
	void cameraControl();
	void selectTarget();

	DataManager *data;// plan to get rid of this
	GameSceneManager *gameSceneManager;
	ObjectManager *objectManager;
	VisualsManager *visualsManager;
	MissionManager *missionManager;
	PlayerCamera *playerCam;
	Player *player;
	HUD *hud;
	Intercom *intercom;
	TurningMarker *turning;

	//ui members
	StationMenu *stationMenu;
	GameMenu *gameMenu;
};

#endif
