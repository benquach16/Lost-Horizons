#include "stdafx.h"
#include "minimap.h"
#include "globals.h"

using namespace base;

Minimap::Minimap()
{
}

Minimap::~Minimap()
{

}


void Minimap::run()
{
	//get the position of all this ships on a x and z plane
	//and get them relative to the player
	//then we can create a minimap
	

	//first draw a faint black background
	vdriver->draw2DRectangle(video::SColor(64,64,64,64), rect<s32>(0,0,200,200));
	//now we can draw all targetableobjects relative to the player


}
