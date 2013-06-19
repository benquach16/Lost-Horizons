#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

#include "player.h"
#include "keylistener.h"
#include "gamescene.h"

class Gameloop
{
public:
	Gameloop();

	//parameterized constructor
	//really though, not using this is bad news bears
	Gameloop(IrrlichtDevice *graphics, KeyListener *receiver);
	//might want this to be a singleton
	~Gameloop();
	//having an independant function to loop through everything makes pausing much easier
	void run();

private:
	void playerControl();
	void cameraControl();

	IrrlichtDevice *graphics;
	ICameraSceneNode *playerCam;
	KeyListener *receiver;
	Player *player;

	GameScene *currentScene;
};



#endif
