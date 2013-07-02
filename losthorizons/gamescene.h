#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

//Here we manage the current scene and all objects inside of the scene
//We shouldn't deal with creating multiple scenes too much, since an entire solar system should be a single scene
//only for the implementation of multiple solar systems
//so for now, keep the design as a singleton
#include <list>
#include <stack>
#include "player.h"
#include "ship.h"
#include "object.h"
#include "objectmanager.h"
#include "playercamera.h"
#include "keylistener.h"

enum E_GAMESCENES
{
	E_MAINMENU_SCENE,
	E_TAU_CETI_SCENE,
};

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

class GameScene
{
public:
	GameScene();
	//parameterized constructor
	//for creating a specific scene
	GameScene(IrrlichtDevice *graphics, E_GAMESCENES scene = E_MAINMENU_SCENE);
	~GameScene();
	void loadScene();
	void saveScene();
	void run(float frameDeltaTime);

	PlayerCamera *createPlayerCam(const vector3df &position = vector3df(0.f,0.f,0.f));
	Player *createPlayer(const ShipProperties &shipProps, 
		const vector3df &position, const vector3df &rotation);
	Ship *createShip(const vector3df &position, const vector3df &rotation,
		const ShipProperties &shipProps, const E_GAME_FACTIONS &faction);
	PlayerCamera* getCurrentSceneCamera();
	
	
private:
	E_GAMESCENES scene;
	PlayerCamera *playerCam;
	IrrlichtDevice *graphics;
	ISceneNode *skybox;
	std::stack<ISceneNode*> sceneObjects;		//stores static scene node objects
};

#endif
