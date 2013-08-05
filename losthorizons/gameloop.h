#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

#include "keylistener.h"
#include "player.h"
#include "gamescene.h"
#include "datamanager.h"
#include "gamescenemanager.h"
#include "objectmanager.h"
#include "hud.h"

class Gameloop
{
public:
	Gameloop();

	//parameterized constructor
	//really though, not using this is bad news bears
	Gameloop(IrrlichtDevice *graphics, KeyListener *receiver, DataManager *data);
	
	//newgame or loadgame instances
	void createNewGame();
	void createLoadedGame(const std::string &filename);

	GameSceneManager* getGameSceneManager() { return gameSceneManager; }
	Player* getPlayer() { return player; }
	void setPlayer(Player* newPlayer) { player = newPlayer; }

	//might want this to be a singleton
	~Gameloop();
	//having an independant function to loop through everything makes pausing much easier
	void run();

private:
	void playerControl(f32 frameDeltaTime);
	void cameraControl();
	void selectTarget();

	IrrlichtDevice *graphics;
	KeyListener *receiver;
	DataManager *data;
	GameSceneManager *gameSceneManager;
	ObjectManager *objectManager;
	PlayerCamera *playerCam;
	Player *player;
	HUD *hud;

	//for delta time calculation
	f32 then;
};

#endif
