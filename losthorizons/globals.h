// include this file wherever these variables are needed

#include "stdafx.h"
#include "keylistener.h"
#include "gameloop.h"
#include "devconsole.h"

namespace base
{
	extern KeyListener *receiver;
	extern irrklang::ISoundEngine *sound;
	extern irr::IrrlichtDevice *graphics;
	
	extern irr::video::IVideoDriver* vdriver;
	extern irr::scene::ISceneManager* scenemngr;
	extern irr::gui::IGUIEnvironment* guienv;
	extern irr::ITimer* timer;
	extern Gameloop* game;
	extern DevConsole* console;

	extern f32 frameDeltaTime;
	extern u32 width, height;
}
