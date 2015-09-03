#include "stdafx.h"
#include "rearmmenu.h"
#include "globals.h"

#include <iostream>
#pragma hdrstop

using namespace base;
using namespace irr;
using namespace core;
using namespace scene;

const vector3df cameraPosition = vector3df(0,200,0);
const video::SColor renderColor = video::SColor(128,100,120,140);

RearmMenu::RearmMenu()
{
	//make important stuff
	//do render to texture
	window = guienv->addWindow(rect<s32>(width/2-400,height/2-300,width/2+400,height/2+300), false, L"Rearm");
	shipsInFleet = guienv->addListBox(rect<s32>(10,40,60,600),window);
	shipImage = guienv->addImage(rect<s32>(70,20,600,400), window,-1,L"",false);
	//render to texture 
	rt = vdriver->addRenderTargetTexture(core::dimension2d<u32>(base::width/2,base::height/2), "ShipRTT");
	shipCamera = scenemngr->addCameraSceneNode(0,cameraPosition,vector3df(0,0,0),-1,false);

	
	//set the texture to a something	
	

}

RearmMenu::~RearmMenu()
{
	
}

void RearmMenu::loadFleet(const Fleet* fleet)
{
	//load the ships
	for(unsigned i = 0; i < fleet->size(); i++)
	{
		shipsInFleet->addItem(L"1");
	}
}

void RearmMenu::run()
{
	
	Ship *player = Ship::allShips[0];
	
	//this is gunna be a right bitch
	//temporarily swap the cameras
	//THIS MUST BE RUN BEFORE POSTPROCESSING CALLS
	
	if(rt)
	{
		//how do we run this before the render calls?
		
		ICameraSceneNode *cam = scenemngr->getActiveCamera();
		vdriver->setRenderTarget(rt, true, true, renderColor);

		
		scenemngr->setActiveCamera(shipCamera);

		//draaw what we want to draw here
		//scenemngr->drawAll();
		
		//Ship::allShips[0]->getMesh()->render();
		scenemngr->getActiveCamera()->render();
		Ship::allShips[0]->getMesh()->render();
		//draw boxes aroundthe ship turret slots
		// set back old render target
		// The buffer might have been distorted, so clear it
		//TODO: get rid of vector copying here
		//std::vector<vector2d<s32> > medTurrets = player->getMediumTurretEquipPosition();
		//offset the icon by the center of the picture
		for(unsigned i = 0; i < player->getTurrets(TURRET_HEAVY).size(); i++)
		{
			//player->getTurrets(TURRET_MEDIUM)[i]->renderPosition();
			vector2di t = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(player->getTurrets(TURRET_HEAVY)[i]->getPosition());
			t.X -= 16;
			t.Y -= 16;
			vdriver->draw2DImage(vdriver->getTexture("res/menu/heavy_slot.png"), t, rect<s32>(0,0,32,32), 0, video::SColor(255,255,255,255), true);
		}
		for(unsigned i = 0; i < player->getTurrets(TURRET_MEDIUM).size(); i++)
		{
			//player->getTurrets(TURRET_MEDIUM)[i]->renderPosition();
			vector2di t = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(player->getTurrets(TURRET_MEDIUM)[i]->getPosition());
			t.X -= 16;
			t.Y -= 16;
			vdriver->draw2DImage(vdriver->getTexture("res/menu/medium_slot.png"), t, rect<s32>(0,0,32,32), 0, video::SColor(255,255,255,255), true);
		}
		for(unsigned i = 0; i < player->getTurrets(TURRET_LIGHT).size(); i++)
		{
			//player->getTurrets(TURRET_MEDIUM)[i]->renderPosition();
			vector2di t = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(player->getTurrets(TURRET_LIGHT)[i]->getPosition());
			t.X -= 16;
			t.Y -= 16;
			vdriver->draw2DImage(vdriver->getTexture("res/menu/light_slot.png"), t, rect<s32>(0,0,32,32), 0, video::SColor(255,255,255,255), true);
		}

		vdriver->setRenderTarget(0, true, true, 0);
		//could we draw the render here?

		scenemngr->setActiveCamera(cam);
		effect->render();
		
		//vdriver->draw2DImage(rt, rect<s32>(0,0,base::width/2,base::height/2), rect<s32>(0,0,512,512));
		shipImage->setImage(rt);
	}
}

