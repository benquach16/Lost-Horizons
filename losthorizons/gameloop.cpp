#include "stdafx.h"
#include "gameloop.h"
#include "globals.h"
#include <iostream>
#include <fstream>

using namespace base;

Gameloop::Gameloop(DataManager *data)
	: data(data), gameSceneManager(new GameSceneManager), missionManager(new MissionManager),
	  objectManager(new ObjectManager), visualsManager(new VisualsManager), musicManager(new MusicManager),
	  player(0), intercom(0)
{
}

Gameloop::~Gameloop()
{
	//clear everything we created
	missionList.clear();
	delete gameSceneManager;
	delete missionManager;
	delete objectManager;
	delete visualsManager;
	delete musicManager;
	//do something about this so we dont overdelete the player
	delete player;
}

void Gameloop::init()
{
	gameSceneManager->createScene();
	//missionManager->addMission(MissionProperties("missions/tutorial.xml"));
}

// http://gizmodo.com/5426453/the-physics-of-space-battles
void Gameloop::run()
{
	//run through all essential objects and functions
	player->run();
	gameSceneManager->run();
	missionManager->run(intercom);
	
	visualsManager->run();
}

void Gameloop::createNewGame()
{
	//reset things
	gameSceneManager->destroyScene();
	gameSceneManager->changeCurrentScene(SCENE_TAU_CETI);
	TargetableObject::nextID = 0;
	//create player ship
	gameSceneManager->createShip(FACTION_TERRAN);

	//temporary for testing purposes only
	Ship *p = gameSceneManager->createShip(FACTION_TERRAN, ObjectManager::E_SHIP_LIST::PRAE_CRUISER, vector3df(500,0,0));
	player->getShip()->getFleet()->addShipToFleet(p);
	init();
}

void Gameloop::createLoadedGame(const std::string &filename)
{
	data->load(filename);
}// plan to get rid of this and just do things from the savemenu class

void Gameloop::loadMissionList()
{
	//load missions into this class
	std::ifstream file("missions/list");
	std::string input;
	while(getline(file, input))
	{
		
		//parse the mission file i guess
		MissionProperties p(input);
		missionList.push_back(p);
	}
}

void Gameloop::addMissionFromList(const int i)
{
	missionManager->addMission(missionList[i]);
}

const std::vector<MissionProperties> Gameloop::getMissionList() const
{
	return missionList;
}

GameSceneManager *Gameloop::getGameSceneManager() const
{
	return gameSceneManager;
}

MissionManager *Gameloop::getMissionManager() const
{
	return missionManager;
}

void Gameloop::setPointers(Player* player, Intercom *intercom)
{
	this->player = player;
	this->intercom = intercom;
}
