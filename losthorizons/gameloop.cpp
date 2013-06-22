//#include "stdafx.h"
#include "gameloop.h"

Gameloop::Gameloop()
{
}

Gameloop::Gameloop(IrrlichtDevice *graphics, KeyListener *receiver) : 
	currentScene(new GameScene(graphics)), objectManager(new ObjectManager(graphics)),
	graphics(graphics), receiver(receiver)
{
	//create player and camera
	
}

Gameloop::~Gameloop()
{
}

void Gameloop::run()
{
	playerControl();
	currentScene->run();
}

void Gameloop::playerControl()
{
	//all actions the player can do are stored here
	if(receiver->isKeyDown(irr::KEY_KEY_X))
	{
		//accelerate

	}
	else if(receiver->isKeyDown(irr::KEY_KEY_Z))
	{
		//decelerate
	}
}

