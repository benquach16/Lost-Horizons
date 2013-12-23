#include "stdafx.h"
#include "minimap.h"
#include "globals.h"

#define SHIPWIDTH 2
#define FIGWIDTH 1
#define DEFAULTZOOM 0.025

using namespace base;



Minimap::Minimap() : zoomFactor(DEFAULTZOOM), enlarged(false)
{
}

Minimap::~Minimap()
{

}


void Minimap::run()
{
	if(!enlarged)
		runRegular();
	else
		runEnlarged();
}

void Minimap::zoomIn()
{
	zoomFactor = zoomFactor*2;
}

void Minimap::zoomOut()
{
	zoomFactor = zoomFactor/2;
}

void Minimap::enlarge()
{
	//hoo boy
	if(!enlarged)
		enlarged=true;
	else
		enlarged=false;
}

//protected functions
void Minimap::runRegular()
{

	//get the position of all this ships on a x and z plane
	//and get them relative to the player
	//then we can create a minimap
	//vdriver->draw2DRectangle(video::SColor(64,64,64,64), rect<s32>(0,0,200,200));
	vdriver->draw2DImage(vdriver->getTexture("res/menu/minimap.png"), position2d<s32>(), rect<s32>(0,0,256,256), 0, video::SColor(255,255,255,255), true);
	vector3df playerPosition = Ship::allShips[0]->getPosition();
	vector3df playerRotation = Ship::allShips[0]->getRotation();
	//now we can draw all targetableobjects relative to the player
	for(unsigned i = 0; i < TargetableObject::allTargets.size(); i++)
	{
		//get relative postiion in x and z to playership
		//then scale them to 200x200
		
		f32 x = playerPosition.X-TargetableObject::allTargets[i]->getPosition().X;
		f32 z = playerPosition.Z-TargetableObject::allTargets[i]->getPosition().Z;
		//if its too large then we bail
		x=x*-zoomFactor;
		z=z*zoomFactor;
		//x = x*cos((playerRotation.Y*3.1415)/180);
		//z = z*sin((playerRotation.Y*3.1415)/180);		
		x+=100;
		z+=100;
		
		//make sure to adjust it by like the direction the player is facing
		//make sure that that icon is within 200 200
		if(x < 200.f && z < 200.f)
		{
		//if(TargetableObject::allTargets[i]->getTargetableObjectType() == TARGETABLEOBJECT_SHIP)
			if(Ship::allShips[0]->getShipTarget() == TargetableObject::allTargets[i])
			{
				//white box
				vdriver->draw2DRectangle(video::SColor(255, 255,255, 255), rect<s32>((s32)(x-SHIPWIDTH-1), (s32)(z-SHIPWIDTH-1),
																				(s32)(x+SHIPWIDTH+1), (s32)(z+SHIPWIDTH+1)));
			}
			else
			{
				vdriver->draw2DRectangle(video::SColor(255, 0, 0, 255), rect<s32>((s32)(x-SHIPWIDTH), (s32)(z-SHIPWIDTH),
																				(s32)(x+SHIPWIDTH), (s32)(z+SHIPWIDTH)));
			}
		}
	}
	//fuck it we'll just draw a line for player orientation
	playerRotation.Y-=90;
	double x = 30*cos((double)(playerRotation.Y*3.1415)/180);
	double y = 30*sin((double)(playerRotation.Y*3.1415)/180);
	x+=100;
	y+=100;
	vdriver->draw2DLine(position2d<s32>(100,100),position2d<s32>((s32)x,(s32)y),
											video::SColor(255,128,128,128));
	
	//player position at 100x100
	//we use boxes for now because we are ghetto
	vdriver->draw2DRectangle(video::SColor(255, 0, 255, 0), rect<s32>((100-SHIPWIDTH), (100-SHIPWIDTH),
																	(100+SHIPWIDTH), (100+SHIPWIDTH)));	
}

void Minimap::runEnlarged()
{

}
