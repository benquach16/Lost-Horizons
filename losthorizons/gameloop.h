#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

#include "player.h"
#include "keylistener.h"

class Gameloop
{
public:
	Gameloop();

	//parameterized constructor
	//really though, not using this is bad news bears
	Gameloop(IrrlichtDevice *graphics, KeyListener receiver);
	//might want this to be a singleton
	~Gameloop();
	//having an independant function to loop through everything makes pausing much easier
	void run();
	void playerControl();

private:
	IrrlichtDevice *graphics;
	KeyListener *receiver;
	Player *player;
};

#endif
