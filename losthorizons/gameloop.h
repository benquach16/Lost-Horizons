#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

#include "gamescene.h"
#include "datamanager.h"
#include "gamescenemanager.h"
#include "missionmanager.h"
#include "objectmanager.h"
#include "musicmanager.h"
#include "visualsmanager.h"
#include "player.h"
#include "intercom.h"

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
	//move missionloading into this class
	void loadMissionList();
	void addMissionFromList(const int i);
	const std::vector<MissionProperties> getMissionList() const;

	//functions for managing the scene
	GameSceneManager *getGameSceneManager() const;
	MissionManager *getMissionManager() const;
	//hacky function :(
	void setPointers(Player* player, Intercom *intercom);

private:
	std::vector<MissionProperties> missionList;
	DataManager *data;// plan to get rid of this
	GameSceneManager *gameSceneManager;
	MissionManager *missionManager;
	ObjectManager *objectManager;
	VisualsManager *visualsManager;
	MusicManager *musicManager;
	Player *player;
	Intercom *intercom;
};

#endif
