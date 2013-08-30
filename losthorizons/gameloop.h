#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

#include "keylistener.h"
#include "player.h"
#include "gamescene.h"
#include "datamanager.h"
#include "gamescenemanager.h"
#include "objectmanager.h"
#include "visualsmanager.h"
#include "hud.h"
#include "turningmarker.h"
#include "stationmenu.h"
#include "gamemenu.h"

class Gameloop
{
public:
	Gameloop();
	Gameloop(IrrlichtDevice *graphics, KeyListener *receiver, DataManager *data);
	~Gameloop();
	void init();
	void run(f32 frameDeltaTime);

	//newgame or loadgame instances
	void createNewGame();
	void createLoadedGame(const std::string &filename);

	//functions for managing the scene
	GameSceneManager *getGameSceneManager() { return gameSceneManager; } const
	void setPlayer(Player* newPlayer) { player = newPlayer; }

private:
	void playerControl(f32 frameDeltaTime);
	void cameraControl();
	void selectTarget();

	IrrlichtDevice *graphics;
	KeyListener *receiver;
	DataManager *data;// plan to get rid of this
	GameSceneManager *gameSceneManager;
	ObjectManager *objectManager;
	VisualsManager *visualsManager;
	PlayerCamera *playerCam;
	Player *player;
	HUD *hud;
	TurningMarker *turning;

	//ui members
	StationMenu *stationMenu;
	GameMenu *gameMenu;
};

#endif
