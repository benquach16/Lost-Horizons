#include "stdafx.h"
#include "musicmanager.h"
#include "globals.h"

std::vector<char*> trackList;

MusicManager::MusicManager() : currentTrack(TRACK_MAINMENU), currentSound(0)
{
	//initialize the enums to filepaths
	trackList.push_back("res/sounds/music/ambient1.mp3");

	currentSound = base::sound->play2D(trackList[currentTrack], true, false, true);
}

MusicManager::~MusicManager()
{
	if(currentSound)
		currentSound->drop();	
}

void MusicManager::changeCurrentTrack(E_TRACK_LIST newTrack)
{

}
