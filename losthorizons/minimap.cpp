#include "stdafx.h"
#include "minimap.h"
#include "globals.h"

#define SHIPWIDTH 2
#define FIGWIDTH 1

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
	//we should definately create an image for this
	//vdriver->draw2DRectangle(video::SColor(64,64,64,64), rect<s32>(0,0,200,200));
	vdriver->draw2DImage(vdriver->getTexture("res/menu/minimap.png"), position2d<s32>(), rect<s32>(0,0,256,256), 0, video::SColor(255,255,255,255), true);
	vector3df playerPosition = Ship::allShips[0]->getPosition();
	vector3df playerRotation = Ship::allShips[0]->getRotation();
	//now we can draw all targetableobjects relative to the player
	for(unsigned i = 0; i < TargetableObject::allTargets.size(); i++)
	{
		//get relative postiion in x and z to playership
		//then scale them to 200x200
		
		float x = playerPosition.X-TargetableObject::allTargets[i]->getPosition().X;
		float z = playerPosition.Z-TargetableObject::allTargets[i]->getPosition().Z;
		//if its too large then we bail
		//x=x*sin(playerRotation.Y);
		//z=z*cos(playerRotation.Y);
		x=x*-0.1;
		z=z*0.1;
		//x = x*cos((playerRotation.Y*3.1415)/180);
		//z = z*sin((playerRotation.Y*3.1415)/180);		
		x+=100;
		z+=100;
		
		//make sure to adjust it by like the direction the player is facing

		//make sure that that icon is within 200 200
		if(x < 200.f && z < 200.f)
		//if(TargetableObject::allTargets[i]->getTargetableObjectType() == TARGETABLEOBJECT_SHIP)
		vdriver->draw2DRectangle(video::SColor(255, 0, 0, 255), rect<s32>((x-SHIPWIDTH), (z-SHIPWIDTH),
																																			(x+SHIPWIDTH), (z+SHIPWIDTH)));
	}
	//fuck it we'll just draw a line for player orientation
	playerRotation.Y-=90;
	float x = 30*cos((playerRotation.Y*3.1415)/180);
	float y = 30*sin((playerRotation.Y*3.1415)/180);
	x+=100;
	y+=100;
	vdriver->draw2DLine(position2d<s32>(100,100),position2d<s32>(x,y),
											video::SColor(255,128,128,128));
	
	//player position at 100x100
	//we use boxes for now because we are ghetto
	vdriver->draw2DRectangle(video::SColor(255, 0, 255, 0), rect<s32>((100-SHIPWIDTH), (100-SHIPWIDTH),
																																		(100+SHIPWIDTH), (100+SHIPWIDTH)));

}
