#ifndef _CONFIG_H_
#define _CONFIG_H_

// include this header file whenever you want to use the config

#include <string>


struct Config
{
	public:
		Config();
		~Config();

		// Whether to save the config on close.
		bool bSaveSettings;
		bool bOverride;

		bool bFirstRun;

		// General
		bool bAutoLoadLast;
		bool bConfirmOnQuit;
		int iWindowX;
		int iWindowY;
		bool bTopMost;

		// Video
		int iResolutionX;
		int iResolutionY;
		bool bFullScreen;
		bool bVsync;
		bool bQuality;
		char cDriver;

		// Audio
		int iMusic;
		int iSFX;
		
		// UI
		bool bShowFPSCounter;
		bool bShowDebugStats;

		// functions
		void Load(const char *iniFileName = "config.ini");
		void Save();

	private:
		std::string iniFilename_;
};
extern Config gConfig;

#endif
