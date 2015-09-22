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

WeaponSlot::WeaponSlot(E_TURRET_CLASS type, irr::core::vector2di position) :
	type(type), position(position)
{
}

void WeaponSlot::draw()
{
	//draw stuff
	//inc bad code
	if(type == TURRET_HEAVY)
	{
		vdriver->draw2DImage(vdriver->getTexture("res/menu/heavy_slot.png"), position, rect<s32>(0,0,32,32), 0, video::SColor(255,255,255,255), true);
	}
	else if(type == TURRET_MEDIUM)
	{
		vdriver->draw2DImage(vdriver->getTexture("res/menu/medium_slot.png"), position, rect<s32>(0,0,32,32), 0, video::SColor(255,255,255,255), true);
	}
	else if(type == TURRET_LIGHT)
	{
		vdriver->draw2DImage(vdriver->getTexture("res/menu/light_slot.png"), position, rect<s32>(0,0,32,32), 0, video::SColor(255,255,255,255), true);
	}

}

bool WeaponSlot::getWithinBoundingBox()
{
	int x = receiver->getMouseX();
	int y = receiver->getMouseY();
	//make sure the mouse is within the slot
	return ((x > position.X - 16 ) && (x < position.X + 16) && (y > position.Y - 16) && (y < position.Y + 16));
}


RearmMenu::RearmMenu() : currentSelected(-1)
{
	//make important stuff
	//do render to texture
	window = guienv->addWindow(rect<s32>(width/2-400,height/2-300,width/2+400,height/2+300), false, L"Rearm");
	availableWeapons = guienv->addListBox(rect<s32>(10,410,100,600),window);
	shipsInFleet = guienv->addListBox(rect<s32>(10,40,60,400),window);
	shipImage = guienv->addImage(rect<s32>(70,20,600,400), window,-1,L"",false);
	//render to texture 
	rt = vdriver->addRenderTargetTexture(core::dimension2d<u32>(base::width/2,base::height/2), "ShipRTT");
	shipCamera = scenemngr->addCameraSceneNode(0,cameraPosition,vector3df(0,0,0),-1,false);

	
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

void RearmMenu::reloadShip(Ship *ship)
{
	weaponImages.clear();
	for(unsigned i = 0; i < ship->getTurrets(TURRET_HEAVY).size(); i++)
	{
		vector2di t = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(ship->getTurrets(TURRET_MEDIUM)[i]->getPosition());
		t.X -= 16;
		t.Y -= 16;
		weaponImages.push_back(WeaponSlot(TURRET_HEAVY,t));
	}
	for(unsigned i = 0; i < ship->getTurrets(TURRET_MEDIUM).size(); i++)
	{
		vector2di t = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(ship->getTurrets(TURRET_MEDIUM)[i]->getPosition());
		t.X -= 16;
		t.Y -= 16;
		weaponImages.push_back(WeaponSlot(TURRET_MEDIUM,t));
	}
	for(unsigned i = 0; i < ship->getTurrets(TURRET_LIGHT).size(); i++)
	{
		vector2di t = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(ship->getTurrets(TURRET_LIGHT)[i]->getPosition());
		t.X -= 16;
		t.Y -= 16;
		weaponImages.push_back(WeaponSlot(TURRET_LIGHT,t));
	}
}

void RearmMenu::run()
{
	//make sure we stop running once the window is closed
	
	Ship *player = Ship::allShips[0];
	//this is gunna be a right bitch
	//temporarily swap the cameras
	//THIS MUST BE RUN BEFORE POSTPROCESSING CALLS
	
	if(rt && (shipsInFleet->getSelected() != -1))
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

		//swap code
		if(currentSelected != shipsInFleet->getSelected())
		{
			currentSelected = shipsInFleet->getSelected();
			reloadShip(Ship::allShips[0]);
		}
		//draw boxes aroundthe ship turret slots
		// set back old render target
		// The buffer might have been distorted, so clear it
		for(int i = 0; i < weaponImages.size(); i++)
		{
			weaponImages[i].draw();
			if(weaponImages[i].getWithinBoundingBox() && (receiver->isKeyPressed(irr::KEY_LBUTTON)))
			{
				//pressed a button
				//load the weapon
				std::cout << "Icon clicked!" << std::endl;
			}
		}

		std::vector<ObjectManager::E_ITEM_LIST> weaponsList = player->getInventory().getMediumWeapons();
		vdriver->setRenderTarget(0, true, true, 0);
		//could we draw the render here?

		scenemngr->setActiveCamera(cam);
		effect->render();
		
		//vdriver->draw2DImage(rt, rect<s32>(0,0,base::width/2,base::height/2), rect<s32>(0,0,512,512));
		shipImage->setImage(rt);
	}
}

