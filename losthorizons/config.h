#ifndef _CONFIG_H_
#define _CONFIG_H_

// include this header file whenever you want to use the config

#include <string>

struct Config
{
	Config();
	~Config();

	// Special Use
	bool bSaveSettings;
	bool bRestart;
	bool bPlay;
	bool bExit;
	bool bFirstRun;

	// General
	bool bAutoLoadLast;
	bool bCheckIfSaved;
	bool bTopMost;

	// Video
	unsigned iBits;
	unsigned iResolutionX;
	unsigned iResolutionY;
	bool bFullScreen;
	bool bVsync;
	//bool bShaders;

	// Audio
	unsigned iMusic;
	unsigned iSFX;
		
	// UI
	bool bShowFPSCounter;
	bool bShowDebugStats;

	// functions
	void Load(const char *iniFileName = "config.ini");
	void Save();

	std::string iniFilename_;
};
extern Config gConfig;

#endif
