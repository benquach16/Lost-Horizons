#ifndef _CONFIG_H_
#define _CONFIG_H_
#define vdriver gConfig.VideoDriver
#define scenemngr gConfig.SceneManager
#define guienv gConfig.GUIEnvironment
#define timer gConfig.Timer
#define iWidth gConfig.screen.Width
#define iHeight gConfig.screen.Height
#define game gConfig.gGame

// include this header file whenever you want to use the config

#include <string>
#include "irrlicht.h"
#include "gameloop.h"

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

	// pseudo global objects
	irr::video::IVideoDriver* VideoDriver;
	irr::scene::ISceneManager* SceneManager;
	irr::gui::IGUIEnvironment* GUIEnvironment;
	irr::ITimer* Timer;
	irr::core::dimension2d<unsigned> screen;
	Gameloop* gGame;
};
extern Config gConfig;

#endif
