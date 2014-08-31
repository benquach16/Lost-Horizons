#ifndef _MUSICMANAGER_H_
#define _MUSICMANAGER_H_

#include <vector>

#include "irrklang.h"

//manage the musics.
//this will be alot handier when we actually get new music.....
class MusicManager
{
public:
	enum E_TRACK_LIST
	{
		TRACK_MAINMENU,
		TRACK_PEACE
	};
	std::vector<char*> trackList;	

	MusicManager();
	~MusicManager();
	//change the currrent track
	void changeCurrentTrack(E_TRACK_LIST newTrack);
protected:
	E_TRACK_LIST currentTrack;
	irrklang::ISound *currentSound;
};
#endif
