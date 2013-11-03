#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

#include "gamescene.h"
#include "datamanager.h"
#include "gamescenemanager.h"
#include "missionmanager.h"
#include "objectmanager.h"
#include "visualsmanager.h"
#include "player.h"
#include "hud.h"
#include "intercom.h"
#include "turningmarker.h"
#include "gamemenu.h"
#include "stationmenu.h"

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
	GameSceneManager *getGameSceneManager() const;
	void setPlayer(Player* newPlayer);

private:
	void playerControl();
	void cameraControl();

	DataManager *data;// plan to get rid of this
	GameSceneManager *gameSceneManager;
	MissionManager *missionManager;
	ObjectManager *objectManager;
	VisualsManager *visualsManager;
	PlayerCamera *playerCam;
	Player *player;
	HUD *hud;
	Intercom *intercom;
	TurningMarker *turning;

	//ui members
	GameMenu *gameMenu;
	StationMenu *stationMenu;
};

#endif
