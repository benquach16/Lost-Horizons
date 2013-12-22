#include "stdafx.h"
#include "minimap.h"
#include "globals.h"

#define BOXWIDTH 2

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
	for(unsigned i = 0; i < TargetableObject::allTargets.size(); i++)
	{
		//get relative postiion in x and z to playership
		//then scale them to 200x200
		vector3df playerPosition = Ship::allShips[0]->getPosition();
		vector3df playerRotation = Ship::allShips[0]->getRotation();
		float x = playerPosition.X-TargetableObject::allTargets[i]->getPosition().X;
		float z = playerPosition.Z-TargetableObject::allTargets[i]->getPosition().Z;
		//if its too large then we bail
		//x=x*sin(playerRotation.Y);
		//z=z*cos(playerRotation.Y);
		x=x*-0.1;
		z=z*0.1;
		
		x+=100;
		z+=100;
		
		//make sure to adjust it by like the direction the player is facing
		//if(TargetableObject::allTargets[i]->getTargetableObjectType() == TARGETABLEOBJECT_SHIP)
		vdriver->draw2DRectangle(video::SColor(255, 0, 0, 255), rect<s32>((x-BOXWIDTH), (z-BOXWIDTH),
																																			(x+BOXWIDTH), (z+BOXWIDTH)));
	}
	//player position at 100x100
	//we use boxes for now because we are ghetto
	vdriver->draw2DRectangle(video::SColor(255, 0, 255, 0), rect<s32>((100-BOXWIDTH), (100-BOXWIDTH),
																																		(100+BOXWIDTH), (100+BOXWIDTH)));
}
