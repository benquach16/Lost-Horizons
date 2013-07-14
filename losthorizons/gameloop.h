#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

#include "player.h"
#include "keylistener.h"
#include "gamescene.h"
#include "gamescenemanager.h"
#include "objectmanager.h"

class Gameloop
{
public:
	Gameloop();

	//parameterized constructor
	//really though, not using this is bad news bears
	Gameloop(IrrlichtDevice *graphics, KeyListener *receiver);
	
	//newgame or loadgame instances
	void createNewGame();
	void createLoadedGame();

	//might want this to be a singleton
	~Gameloop();
	//having an independant function to loop through everything makes pausing much easier
	void run();

private:
	void playerControl(f32 frameDeltaTime);
	void cameraControl();

	IrrlichtDevice *graphics;
	PlayerCamera *playerCam;
	ObjectManager *objectManager;
	KeyListener *receiver;
	Player *player;

	GameSceneManager *gameSceneManager;

	//for delta time calculation
	f32 then;
};



#endif
