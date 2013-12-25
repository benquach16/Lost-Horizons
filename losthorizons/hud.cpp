#include "stdafx.h"
#include "hud.h"
#include "globals.h"

using namespace base;

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
	targetName = guienv->addStaticText(L"No Target Selected", rect<s32>(0,0,120,120), false, true, targetBkg);
	targetFaction = guienv->addStaticText(L"", rect<s32>(0,15,120,120), false, true, targetBkg);
	targetDistance = guienv->addStaticText(L"", rect<s32>(0,30,120,120), false, true, targetBkg);
	targetHull = guienv->addStaticText(L"", rect<s32>(0,45,120,120), false, true, targetBkg);
	targetArmor = guienv->addStaticText(L"", rect<s32>(0,60,120,120), false, true, targetBkg);
	targetShield = guienv->addStaticText(L"", rect<s32>(0,75,120,120), false, true, targetBkg);
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
}

//private function
void HUD::updatePlayerInfo(const ShipInformation &info)
{
	//lets change the color based on damage
	velocity->setText((core::stringw((int)info.velocity) + L"km/s").c_str());
	hull->setText((core::stringw(L"Hull [") + core::stringw(info.hull) + L"]").c_str());
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
	armor->setText((core::stringw(L"Armor [") + core::stringw(info.armor) + L"]").c_str());
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

	shield->setText((core::stringw(L"Shield [") + core::stringw(info.shield) + L"]").c_str());
	energy->setText((core::stringw(L"Energy [") + core::stringw(info.energy) + L"]").c_str());
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
			targetHull->setText((core::stringw(L"Hull [") + core::stringw(shipTarget->getInfo().hull) + L"]").c_str());
			targetArmor->setText((core::stringw(L"Armor [") + core::stringw(shipTarget->getInfo().armor) + L"]").c_str());
			targetShield->setText((core::stringw(L"Shield [") + core::stringw(shipTarget->getInfo().shield) + L"]").c_str());
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
