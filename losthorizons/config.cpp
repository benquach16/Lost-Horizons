//#include "base/display.h"
#include "config.h"
#include "lib/ini_file.h"

Config gConfig;


Config::Config()
{
}

Config::~Config()
{
}

void Config::Load(const char *iniFileName)
{
	iniFilename_ = iniFileName;
	bSaveSettings = true;

	IniFile iniFile;
	if (!iniFile.Load(iniFileName)) {
		// log here in debug mode
		// Continue anyway; defaults will be used
	}

	IniFile::Section *general = iniFile.GetOrCreateSection("General");

	general->Get("FirstRun", &bFirstRun, true);
	general->Get("AutoLoadLast", &bAutoLoadLast, false);
	general->Get("ConfirmOnQuit", &bConfirmOnQuit, false);
	general->Get("WindowPositionX", &iWindowX, 40);
	general->Get("WindowPositionY", &iWindowY, 20);
	general->Get("TopMost", &bTopMost, false);

	IniFile::Section *graphics = iniFile.GetOrCreateSection("Graphics");

	graphics->Get("ShowFPSCounter", &bShowFPSCounter, false);
	graphics->Get("ResolutionX", &iResolutionX, 1024);
	graphics->Get("ResolutionY", &iResolutionY, 768);
	graphics->Get("FullScreen", &bFullScreen, false);
	graphics->Get("Vsync", &bVsync, false);
//	graphics->Get("Quality", &bQuality, true);
//	graphics->Get("Driver", &cDriver);

	IniFile::Section *sound = iniFile.GetOrCreateSection("Sound");

	sound->Get("Music", &iMusic, 100);
	sound->Get("SFX", &iSFX, 100);
}

void Config::Save()
{
	if (iniFilename_.size() && gConfig.bSaveSettings) {
		IniFile iniFile;
		if (!iniFile.Load(iniFilename_.c_str())) {
			// log here in debug mode
		}

		IniFile::Section *general = iniFile.GetOrCreateSection("General");
		
		// Next time won't be the first run
		bFirstRun = false;
		general->Set("FirstRun", bFirstRun);

		general->Set("AutoLoadLast", bAutoLoadLast);
		general->Set("ConfirmOnQuit", bConfirmOnQuit);
		general->Set("WindowPositionX", iWindowX);
		general->Set("WindowPositionY", iWindowY);
		general->Set("TopMost", bTopMost);

		IniFile::Section *graphics = iniFile.GetOrCreateSection("Graphics");

		graphics->Set("ShowFPSCounter", bShowFPSCounter);
		graphics->Set("FullScreen", bFullScreen);
		graphics->Set("ResolutionX", iResolutionX);
		graphics->Set("ResolutionY", iResolutionY);
		graphics->Set("FullScreen", bFullScreen);
		graphics->Set("Vsync", bVsync);
//		graphics->Set("Quality", bQuality);
//		graphics->Set("Driver", cDriver);

		IniFile::Section *sound = iniFile.GetOrCreateSection("Sound");

		sound->Set("Music", iMusic);
		sound->Set("SFX", iSFX);

		if (!iniFile.Save(iniFilename_.c_str())) {
			return;
		}
		// log here in debug mode
		// config saved
	} else {
		// log here in debug mode
		// not saving config
	}
}
