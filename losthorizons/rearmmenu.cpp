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

WeaponSlot::WeaponSlot(E_TURRET_CLASS type, irr::core::vector2di position, int index) :
	type(type), position(position), index(index)
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

bool WeaponSlot::getWithinBoundingBox(int offsetx, int offsety)
{
	int x = receiver->getMouseX();
	int y = receiver->getMouseY();
	//make sure the mouse is within the slot
	return ((x > position.X - 16 + offsetx ) && (x < position.X + 16 + offsetx) && (y > position.Y - 16 + offsety) && (y < position.Y + 16 + offsety));
}

const int WeaponSlot::getIndex() const
{
	return index;
}


RearmMenu::RearmMenu() : currentSelected(-1), currentSelectedSlot(-1)
{
	//make important stuff
	//do render to texture
	window = guienv->addWindow(rect<s32>(width/2-400,height/2-300,width/2+400,height/2+300), false, L"Rearm");
	availableWeapons = guienv->addListBox(rect<s32>(10,410,400,600),window);
	shipsInFleet = guienv->addListBox(rect<s32>(10,20,100,400),window);
	shipImage = guienv->addImage(rect<s32>(110,20,700,400), window,-1,L"",false);
	closeButton = guienv->addButton(rect<s32>(700,400,790,420), window, -1, L"Close");
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
		weaponImages.push_back(WeaponSlot(TURRET_HEAVY,t, i));
	}
	for(unsigned i = 0; i < ship->getTurrets(TURRET_MEDIUM).size(); i++)
	{
		vector2di t = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(ship->getTurrets(TURRET_MEDIUM)[i]->getPosition());
		t.X -= 16;
		t.Y -= 16;
		weaponImages.push_back(WeaponSlot(TURRET_MEDIUM,t, i));
	}
	for(unsigned i = 0; i < ship->getTurrets(TURRET_LIGHT).size(); i++)
	{
		vector2di t = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(ship->getTurrets(TURRET_LIGHT)[i]->getPosition());
		t.X -= 16;
		t.Y -= 16;
		weaponImages.push_back(WeaponSlot(TURRET_LIGHT,t, i));
	}
	
	std::vector<ObjectManager::E_ITEM_LIST> weaponsList = ship->getInventory().getMediumWeapons();
	availableWeapons->clear();
	availableWeaponsPair.clear();
	for(unsigned i = 0, size = weaponsList.size(); i < size; i++)
	{
		availableWeapons->addItem(ObjectManager::itemList[weaponsList[i]]->getName());
		availableWeaponsPair.push_back(weaponsList[i]);
	}
}

void RearmMenu::run()
{
	//make sure we stop running once the window is closed
	
	Ship *player = Ship::allShips[0];
	//this is gunna be a right bitch
	//temporarily swap the cameras
	//THIS MUST BE RUN BEFORE POSTPROCESSING CALLS
	if(closeButton->isPressed())
		window->setVisible(false);
	if(rt && (shipsInFleet->getSelected() != -1) && window->isVisible())
	{
		//how do we run this before the render calls?

		ICameraSceneNode *cam = scenemngr->getActiveCamera();
		vdriver->setRenderTarget(rt, true, true, renderColor);

		
		scenemngr->setActiveCamera(shipCamera);
		shipCamera->setPosition(Ship::allShips[0]->getPosition() + vector3df(0,200,0));
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
			//ghetto way of handling mouse input is to send the position of the texture to the weaponslot then we can offset it
			weaponImages[i].draw();
			if(weaponImages[i].getWithinBoundingBox(shipImage->getAbsolutePosition().UpperLeftCorner.X,shipImage->getAbsolutePosition().UpperLeftCorner.Y) && 
				(receiver->isKeyPressed(irr::KEY_LBUTTON)))
			{
				//pressed a button
				//load the weapon
				currentSelectedSlot = i;
				std::cout << weaponImages[i].getIndex() << std::endl;
			}
		}

		vdriver->setRenderTarget(0, true, true, 0);
		//could we draw the render here?

		scenemngr->setActiveCamera(cam);
		effect->render();
		
		//vdriver->draw2DImage(rt, rect<s32>(0,0,base::width/2,base::height/2), rect<s32>(0,0,512,512));
		shipImage->setImage(rt);

		//do weapon selection code here
		equipWeapons();
	}
}

void RearmMenu::equipWeapons()
{
	int selected = availableWeapons->getSelected();
	if(currentSelectedSlot != -1)
	{
		//means the player has currently selected a slot
		//if the player seelcts a weapon just switch it i guess
		if(selected != -1)
		{
			//get weapon from selected slot
			//add previous weapon into inventory as well
			
			//icky!!!
			ObjectManager::E_ITEM_LIST equippedTurret = Ship::allShips[0]->getTurrets(TURRET_MEDIUM)[currentSelectedSlot]->getTurretType();
			Ship::allShips[0]->setMediumTurret(availableWeaponsPair[selected],currentSelectedSlot);
			Ship::allShips[0]->getInventory().addItem(equippedTurret);
			Ship::allShips[0]->getInventory().removeItem(availableWeaponsPair[selected]);
			currentSelectedSlot = -1;

			currentSelected = -1;
		}
	}
}
