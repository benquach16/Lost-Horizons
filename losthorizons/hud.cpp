#include "stdafx.h"
#include "hud.h"
#include "globals.h"

using namespace base;

const int TARGETINFOSIZE = 120;

//save strings here
const wchar_t HULL_STRING_BEGIN[] = L"Hull [";
const wchar_t ARMOR_STRING_BEGIN[] = L"Armor [";
const wchar_t SHIELD_STRING_BEGIN[] = L"Shield [";
const wchar_t ENERGY_STRING_BEGIN[] = L"Energy [";

//gunna have a huge initializer list here
HUD::HUD()
	: shipWheel(0), velocity(0), hull(0), armor(0), energy(0), shield(0), targetBkg(0), targetName(0),
	  targetFaction(0), targetDistance(0), targetHull(0), targetArmor(0), targetShield(0)
{
	//window = guienv->addGUIElement(gui::EGUIET_ELEMENT);
	
	IGUIFont *largeFont = guienv->getFont("res/font/verdana_large.xml");
	IGUIFont *smallFont = guienv->getFont("res/font/verdana_small.xml");
	shipWheel = guienv->addImage(vdriver->getTexture("res/menu/hud.png"), core::position2d<s32>(-90,height-190), true);
	velocity = guienv->addStaticText(L"velocity", rect<int>(10,height-110,width/2+35,height), false);
	velocity->setOverrideFont(largeFont);
	hull = guienv->addStaticText(L"hull", rect<int>(10,height-70,width/2+35,height), false);
	//hull->setOverrideFont(smallFont);
	armor = guienv->addStaticText(L"armor", rect<int>(10,height-55,width/2+35,height), false);
	//armor->setOverrideFont(smallFont);
	shield = guienv->addStaticText(L"shield", rect<int>(10,height-40,width/2+35,height), false);
	//shield->setOverrideFont(smallFont);
	energy = guienv->addStaticText(L"power", rect<int>(10,height-25,width/2+35,height), false);

	targetBkg = guienv->addImage(vdriver->getTexture("res/menu/target_info.png"), core::position2d<s32>(width-140,20));
	targetName = guienv->addStaticText(L"No Target Selected", rect<s32>(0,0,TARGETINFOSIZE,TARGETINFOSIZE), false, true, targetBkg);
	targetFaction = guienv->addStaticText(L"", rect<s32>(0,15,TARGETINFOSIZE,TARGETINFOSIZE), false, true, targetBkg);
	targetDistance = guienv->addStaticText(L"", rect<s32>(0,30,TARGETINFOSIZE,TARGETINFOSIZE), false, true, targetBkg);
	targetHull = guienv->addStaticText(L"", rect<s32>(0,45,TARGETINFOSIZE,TARGETINFOSIZE), false, true, targetBkg);
	targetArmor = guienv->addStaticText(L"", rect<s32>(0,60,TARGETINFOSIZE,TARGETINFOSIZE), false, true, targetBkg);
	targetShield = guienv->addStaticText(L"", rect<s32>(0,75,TARGETINFOSIZE,TARGETINFOSIZE), false, true, targetBkg);
}

void HUD::run(const Ship *player)
{
	updatePlayerInfo(player->getInfo());
	updateTargetInfo(player, player->getShipTarget());
}

void HUD::setVisible(bool visible)
{
	//window->setVisible(visible);
	shipWheel->setVisible(visible);
	velocity->setVisible(visible);
	targetBkg->setVisible(visible);
	playerShipsInFleet.clear();
}

void HUD::initializePlayerShipsInFleet(Fleet *playerFleet)
{
	
	for(unsigned i = 0; i < playerFleet->size(); i++)
	{
		fleetShipInfo shipInfo;
		shipInfo.bkgImage = guienv->addImage(vdriver->getTexture("res/menu/target_info.png"), core::position2d<s32>(200 * (i+1), height - 130));
		shipInfo.name = guienv->addStaticText(
			playerFleet->getShipsInFleet()[i]->getName(), rect<s32>(0,0,200,200), false, true, shipInfo.bkgImage);

		shipInfo.hull = guienv->addStaticText(HULL_STRING_BEGIN, rect<s32>(0,15,200,200), false, true, shipInfo.bkgImage);
		playerShipsInFleet.push_back(shipInfo);
	}
}

void HUD::updatePlayerShipsInFleet(Fleet *playerFleet)
{
	//update fleet information
	for(unsigned i = 0 ; i < playerFleet->size(); i++)
	{

	}
}

void HUD::setFleetVisible(bool visible)
{
	//this isnt super efficient but therers not many ways to do this
	for(unsigned i = 0; i < playerShipsInFleet.size(); i++)
	{
		playerShipsInFleet[i].bkgImage->setVisible(visible);
	}
}

HUD::~HUD()
{
	shipWheel->remove();
	velocity->remove();
	targetBkg->remove();
	armor->remove();
	hull->remove();
	shield->remove();
	energy->remove();
	for(unsigned i = 0; i < playerShipsInFleet.size(); i++)
	{
		playerShipsInFleet[i].bkgImage->remove();
	}
	playerShipsInFleet.clear();
}


//private function
void HUD::updatePlayerInfo(const ShipInformation &info)
{
	//lets change the color based on damage
	velocity->setText((core::stringw((int)info.velocity) + L"km/s").c_str());
	hull->setText((core::stringw(HULL_STRING_BEGIN) + core::stringw(info.hull) + L"]").c_str());
	if(info.hull < info.maxHull/4)
	{
		hull->setOverrideColor(video::SColor(255,255,0,0));
	}
	else if(info.hull < info.maxHull/2)
	{
		hull->setOverrideColor(video::SColor(255,255,255,0));
	}
	else
		hull->setOverrideColor(video::SColor(255,255,255,255));
	armor->setText((core::stringw(ARMOR_STRING_BEGIN) + core::stringw(info.armor) + L"]").c_str());
	if(info.armor < info.maxArmor/4)
	{
		armor->setOverrideColor(video::SColor(255,255,0,0));
	}
	else if(info.armor < info.maxArmor/2)
	{
		armor->setOverrideColor(video::SColor(255,255,255,0));
	}
	else
		armor->setOverrideColor(video::SColor(255,255,255,255));

	shield->setText((core::stringw(SHIELD_STRING_BEGIN) + core::stringw(info.shield) + L"]").c_str());
	energy->setText((core::stringw(ENERGY_STRING_BEGIN) + core::stringw(info.energy) + L"]").c_str());
	if(info.energy < info.maxEnergy/4)
	{
		energy->setOverrideColor(video::SColor(255,255,0,0));
	}
	else if(info.energy < info.maxEnergy/2)
	{
		energy->setOverrideColor(video::SColor(255,255,255,0));
	}
	else
		energy->setOverrideColor(video::SColor(255,255,255,255));
}

void HUD::updateTargetInfo(const Ship *player, const TargetableObject *target)
{
	if (target) {
		//if a target exists
		targetName->setText(target->getName());
		targetFaction->setText(target->getFactionName());
		targetDistance->setText((core::stringw((int)target->getPosition().getDistanceFrom(player->getPosition())) + L"km").c_str());
		//at this point we pull object information from this thing
		if (target->getTargetableObjectType() == TARGETABLEOBJECT_SHIP) 
		{
			//draw hull armor and shield
			const Ship* shipTarget = (Ship*)target;
			targetHull->setText((core::stringw(HULL_STRING_BEGIN) + core::stringw(shipTarget->getInfo().hull) + L"]").c_str());
			targetArmor->setText((core::stringw(ARMOR_STRING_BEGIN) + core::stringw(shipTarget->getInfo().armor) + L"]").c_str());
			targetShield->setText((core::stringw(SHIELD_STRING_BEGIN) + core::stringw(shipTarget->getInfo().shield) + L"]").c_str());
		}
		else 
		{
			//not a ship so dont draw hull armor or shield
			targetHull->setText(L"");
			targetArmor->setText(L"");
			targetShield->setText(L"");
		}
	} 
	else
	{
		//reset the text
		targetName->setText(L"No Target Selected");
		targetFaction->setText(L"");
		targetDistance->setText(L"");
		targetHull->setText(L"");
		targetArmor->setText(L"");
		targetShield->setText(L"");
	}
}
