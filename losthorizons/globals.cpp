#include "stdafx.h"
#include "globals.h"

namespace base
{
	KeyListener *receiver = 0;
	irrklang::ISoundEngine* sound = 0;
	irr::IrrlichtDevice *graphics = 0;
	irr::video::IVideoDriver* vdriver = 0;
	irr::scene::ISceneManager* scenemngr = 0;
	irr::gui::IGUIEnvironment* guienv = 0;
	irr::ITimer* timer = 0;
	Gameloop* game = 0;
	u32 width = 0, height = 0;
}
