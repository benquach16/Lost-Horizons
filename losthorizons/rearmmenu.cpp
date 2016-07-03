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

E_TURRET_CLASS WeaponSlot::getType() const
{
	return type;
}


RearmMenu::RearmMenu() : currentSelected(-1), currentSelectedSlot(-1)
{
	renderFrame = false;
	//make important stuff
	//do render to texture
	window = guienv->addWindow(rect<s32>(width/2-400,height/2-300,width/2+400,height/2+300), false, L"Rearm");
	availableWeapons = guienv->addListBox(rect<s32>(10,410,400,600),window);
	shipsInFleet = guienv->addListBox(rect<s32>(10,20,100,400),window);
	shipImage = guienv->addImage(rect<s32>(110,20,700,400), window,-1,L"",false);
	closeButton = guienv->addButton(rect<s32>(700,400,790,420), window, -1, L"Close");
	applyButton = guienv->addButton(rect<s32>(600, 400, 690, 420), window, -1, L"Accept");
	//render to texture 
	rt = vdriver->addRenderTargetTexture(core::dimension2d<u32>(base::width/2,base::height/2), "ShipRTT");
	shipCamera = scenemngr->addCameraSceneNode(0,cameraPosition,vector3df(0,0,0),-1,false);
	weaponTitle = guienv->addStaticText(L"", rect<s32>(410, 430, 790, 450), true, true, window);
	description = guienv->addStaticText(L"", rect<s32>(410,460, 790, 590),true, true, window);
}

RearmMenu::~RearmMenu()
{
	
}

void RearmMenu::loadFleet(const Fleet* fleet)
{
	//load the ships
	this->fleet = fleet;
	for(unsigned i = 0; i < fleet->size(); i++)
	{
		shipsInFleet->addItem(fleet->getShipsInFleet()[i]->getName());
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
	
	availableWeapons->clear();
	availableWeaponsPair.clear();
	weaponTitle->setText(L"");
	description->setText(L"");

}
void RearmMenu::run()
{
	//make sure we stop running once the window is closed
	
	//this is gunna be a right bitch
	//temporarily swap the cameras
	//THIS MUST BE RUN BEFORE POSTPROCESSING CALLS
	if(closeButton->isPressed())
		window->setVisible(false);
	int selected = shipsInFleet->getSelected();
	if(rt && (selected != -1) && window->isVisible())
	{

		//draw boxes aroundthe ship turret slots
		// set back old render target
		// The buffer might have been distorted, so clear it
		if(!renderFrame)
		{
			renderOneFrame();
			renderFrame = true;
		}
		//swap code
		

		for(unsigned i = 0; i < weaponImages.size(); i++)
		{
			//ghetto way of handling mouse input is to send the position of the texture to the weaponslot then we can offset it
			if(weaponImages[i].getWithinBoundingBox(shipImage->getAbsolutePosition().UpperLeftCorner.X + 16,shipImage->getAbsolutePosition().UpperLeftCorner.Y +16) && 
				(receiver->isKeyPressed(irr::KEY_LBUTTON)))
			{
				//pressed a button
				//load the weapon
				currentSelectedSlot = weaponImages[i].getIndex();
				selectedWeaponClass = weaponImages[i].getType();
				std::cout << weaponImages[i].getIndex() << std::endl;
			}
		}
		//do weapon selection code here
		equipWeapons();
	}
}

void RearmMenu::renderOneFrame()
{
	//Render one image into texture so that we don't hog FPS with constant render to texture calls
	int selected = shipsInFleet->getSelected();
	if(rt && selected != -1)
	{
		//how do we run this before the render calls?
		Ship* selectedShip = fleet->getShipsInFleet()[selected];
		ICameraSceneNode *cam = scenemngr->getActiveCamera();
		vdriver->setRenderTarget(rt, true, true, renderColor);

		
		scenemngr->setActiveCamera(shipCamera);
		shipCamera->setPosition(Ship::allShips[0]->getPosition() + vector3df(0,200,0));
		//draaw what we want to draw here
		//scenemngr->drawAll();
		
		//Ship::allShips[0]->getMesh()->render();
		scenemngr->getActiveCamera()->render();
		selectedShip->getMesh()->render();
		if(currentSelected != shipsInFleet->getSelected())
		{
			currentSelected = shipsInFleet->getSelected();
			reloadShip(selectedShip);
		}

		for(int i = 0; i < weaponImages.size(); i++)
		{
			//ghetto way of handling mouse input is to send the position of the texture to the weaponslot then we can offset it
			weaponImages[i].draw();
		}


		vdriver->setRenderTarget(0, true, true, 0);
		//could we draw the render here?

		scenemngr->setActiveCamera(cam);
		effect->render();
		
		//vdriver->draw2DImage(rt, rect<s32>(0,0,base::width/2,base::height/2), rect<s32>(0,0,512,512));
		shipImage->setImage(rt);
	}
}

void RearmMenu::equipWeapons()
{
	int selected = availableWeapons->getSelected();
	if(currentSelectedSlot != -1)
	{
		//means the player has currently selected a slot
		//if the player seelcts a weapon just switch it i guess
		E_TURRET_CLASS currentWeaponClass = selectedWeaponClass;
		ObjectManager::E_ITEM_LIST equippedTurret = Ship::allShips[0]->getTurrets(currentWeaponClass)[currentSelectedSlot]->getTurretType();
		

		//if we have a selected slot display the weapon description in the slot
		weaponTitle->setText(ObjectManager::itemList[equippedTurret]->getName());
		description->setText(ObjectManager::itemList[equippedTurret]->getDesc());
		//make sure we load the avilalbe weapons with the relevant weapons
		if(!availableWeaponsPair.size())
		{
			std::vector<ObjectManager::E_ITEM_LIST> weaponsList = Ship::allShips[0]->getInventory().getMediumWeapons();
			if(currentWeaponClass == TURRET_MEDIUM)
			{
				weaponsList = Ship::allShips[0]->getInventory().getMediumWeapons();
			}
			else if(currentWeaponClass == TURRET_LIGHT)
			{
				weaponsList = Ship::allShips[0]->getInventory().getLightWeapons();
			}
			for(unsigned i = 0, size = weaponsList.size(); i < size; i++)
			{
				availableWeapons->addItem(ObjectManager::itemList[weaponsList[i]]->getName());
				availableWeaponsPair.push_back(weaponsList[i]);
			}
		}
		//LOL
		//this code
		if(selected != -1 && applyButton->isPressed())
		{
			//get weapon from selected slot
			//add previous weapon into inventory as well
			
			//icky!!!
			if(currentWeaponClass == TURRET_MEDIUM)
			{
				Ship::allShips[0]->setMediumTurret(availableWeaponsPair[selected],currentSelectedSlot);
			}
			else if(currentWeaponClass == TURRET_LIGHT)
			{
				Ship::allShips[0]->setLightTurret(availableWeaponsPair[selected],currentSelectedSlot);
			}
			Ship::allShips[0]->getInventory().addItem(equippedTurret);
			Ship::allShips[0]->getInventory().removeItem(availableWeaponsPair[selected]);
			currentSelectedSlot = -1;

			currentSelected = -1;
			renderFrame = false;
			
		}

	}
}
