#include "stdafx.h"
#include "gameloop.h"
#include "globals.h"

using namespace base;

Gameloop::Gameloop(DataManager *data)
	: data(data), gameSceneManager(new GameSceneManager), missionManager(new MissionManager),
	  objectManager(new ObjectManager), visualsManager(new VisualsManager), musicManager(new MusicManager),
		player(0),intercom(0)
{
}

Gameloop::~Gameloop()
{
	//clear everything we created
	delete gameSceneManager;
	delete missionManager;
	delete objectManager;
	delete visualsManager;
	delete musicManager;
	delete player;
}

void Gameloop::init()
{
	gameSceneManager->createScene();
	missionManager->addMission(MissionProperties("missions/tutorial.xml"));
}

void Gameloop::run()
{
	//run through all essential objects and functions
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
	gameSceneManager->createShip(FACTION_TERRAN, ObjectManager::E_SHIP_LIST::PRAE_CRUISER, vector3df(500,0,0));
	gameSceneManager->createShip(FACTION_PIRATE, ObjectManager::E_SHIP_LIST::ISHTAR_CRUISER, vector3df(500,0,2000));
	gameSceneManager->createShip(FACTION_PIRATE, ObjectManager::E_SHIP_LIST::ISHTAR_CRUISER, vector3df(-1000,0,2300));
	gameSceneManager->createShip(FACTION_NEUTRAL, ObjectManager::E_SHIP_LIST::EAGLE_FREIGHTER, vector3df(-400,0,-400));
	gameSceneManager->createStation(FACTION_TERRAN, ObjectManager::E_STATION_LIST::TRADING, vector3df(1000,0,500));
	gameSceneManager->createStation(FACTION_TERRAN, ObjectManager::E_STATION_LIST::SHIPYARD, vector3df(2000,-100,-2000));

	init();
}

void Gameloop::createLoadedGame(const std::string &filename)
{
	data->load(filename);
}// plan to get rid of this and just do things from the savemenu class

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
