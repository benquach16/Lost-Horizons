// losthorizons.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "baseapplication.h"
#include "config.h"

void getCmdArgs(int argc, char *argv[])
{
	bool args = false;
	for (int i = 1; i < argc; ++i) {
		if (argv[i] == "-fullscreen") {
			gConfig.bFullScreen = true;
			args = true;
		}
		if (argv[i] == "-debug") {
			gConfig.bFirstRun = false;
			gConfig.bCheckIfSaved = false;
			gConfig.bTopMost = false;
			gConfig.bShowFPSCounter = true;
			gConfig.bShowDebugStats = true;
			args = true;
		}
	}
	if (args) {
		gConfig.bSaveSettings = false;
	}
}

int main(int argc, char* argv[])
{
	BaseApplication app;

	//We can get command line arguments here
	getCmdArgs(argc, argv);
	
	app.init();
	app.run();
	return 0;
}
