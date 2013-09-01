#include "stdafx.h"
#include "hud.h"
#include <sstream>

//gunna have a huge initializer list here
HUD::HUD(Player *player) : shipWheel(0), velocity(0), hull(0), armor(0), shield(0), targetBkg(0), targetName(0), player(player), 
	targetFaction(0), targetDistance(0), targetHull(0), targetArmor(0), targetShield(0), intercom(new Intercom(player))

{
	//window = guienv->addGUIElement(gui::EGUIET_ELEMENT);
	initializeDisplay();
}

void HUD::initializeDisplay()
{
	IGUIFont *largeFont = guienv->getFont("res/font/verdana_large.xml");
	IGUIFont *smallFont = guienv->getFont("res/font/verdana_small.xml");
	shipWheel = guienv->addImage(vdriver->getTexture("res/menu/hud.png"), core::position2d<s32>(-90,iHeight-190), true);
	velocity = guienv->addStaticText(L"velocity", rect<int>(10,iHeight-110,iWidth/2+35,iHeight), false);
	velocity->setOverrideFont(largeFont);
	hull = guienv->addStaticText(L"hull", rect<int>(10,iHeight-70,iWidth/2+35,iHeight), false);
	//hull->setOverrideFont(smallFont);
	armor = guienv->addStaticText(L"armor", rect<int>(10,iHeight-55,iWidth/2+35,iHeight), false);
	//armor->setOverrideFont(smallFont);
	shield = guienv->addStaticText(L"shield", rect<int>(10,iHeight-40,iWidth/2+35,iHeight), false);
	//shield->setOverrideFont(smallFont);

	targetBkg = guienv->addImage(vdriver->getTexture("res/menu/target_info.png"), core::position2d<s32>(iWidth-140,20));
	targetName = guienv->addStaticText(L"No Target Selected", rect<s32>(0,0,120,120), false, true, targetBkg);
	targetFaction = guienv->addStaticText(L"", rect<s32>(0,15,120,120), false, true, targetBkg);
	targetDistance = guienv->addStaticText(L"", rect<s32>(0,30,120,120), false, true, targetBkg);
	targetHull = guienv->addStaticText(L"", rect<s32>(0,45,120,120), false, true, targetBkg);
	targetArmor = guienv->addStaticText(L"", rect<s32>(0,60,120,120), false, true, targetBkg);
	targetShield = guienv->addStaticText(L"", rect<s32>(0,75,120,120), false, true, targetBkg);
}

void HUD::run()
{
	intercom->run();
	updatePlayerInfo();
	updateTargetInfo();
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
	delete intercom;
}

//private function
void HUD::updatePlayerInfo()
{
	core::stringw str(L"");
	str += (int)player->getInfo().velocity;
	str += L"km/s";
	velocity->setText(str.c_str());

	str= L"Hull [";
	str += (int)player->getInfo().hull;
	str+="]";
	hull->setText(str.c_str());

	str= L"Armor [";
	str += (int)player->getInfo().armor;
	str+="]";
	armor->setText(str.c_str());

	str= L"Shield [";
	str += (int)player->getInfo().shield;
	str+="]";
	shield->setText(str.c_str());
}

void HUD::updateTargetInfo()
{
	const TargetableObject *target = player->getShipTarget();
	if(target)
	{
		//if a target exists
		targetName->setText(target->getName().c_str());
		targetFaction->setText(getFactionName(target->getFaction()));
		//calculate distance
		int distance = (int)target->getPosition().getDistanceFrom(player->getPosition());
		core::stringw d(L"");
		d+=distance;
		d+= L"km";
		targetDistance->setText(d.c_str());
		//at this point we pull object information from this thing
		if(target->getTargetableObjectType() == E_OBJECT_SHIP)
		{
			//draw hull armor and shield
			const Ship* shipTarget = (Ship*)target;
			std::wstring str(L"Hull [");
			str += std::to_wstring(shipTarget->getInfo().hull);
			str += L"]";
			targetHull->setText(str.c_str());
			str = L"Armor [";
			str += std::to_wstring(shipTarget->getInfo().armor);
			str += L"]";
			targetArmor->setText(str.c_str());
			str = L"Shield [";
			str += std::to_wstring(shipTarget->getInfo().shield);
			str += L"]";
			targetShield->setText(str.c_str());
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

const wchar_t *HUD::getFactionName(E_GAME_FACTIONS faction)
{
	if(faction == E_FACTION_NEUTRAL)
	{
		return L"Neutral";
	}
	else if(faction == E_FACTION_PIRATE)
	{
		return L"Pirate";
	}
	else if(faction == E_FACTION_TERRAN)
	{
		return L"Terran Federation";
	}
	else if(faction == E_FACTION_PROVIAN)
	{
		return L"Provian Consortium";
	}
	else
		return L"Unknown";
}
