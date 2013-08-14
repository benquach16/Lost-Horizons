#include "stdafx.h"
#include "hud.h"


//gunna have a huge initializer list here
HUD::HUD(Player *player) : shipWheel(0), velocity(0), hull(0), armor(0), shield(0), targetBkg(0), targetName(0), player(player)
{
	//window = guienv->addGUIElement(gui::EGUIET_ELEMENT);
	initializeDisplay();
}

void HUD::initializeDisplay()
{
	IGUIFont *largeFont = guienv->getFont("res/font/verdana_large.xml");
	shipWheel = guienv->addImage(vdriver->getTexture("res/menu/hud.png"), core::position2d<s32>(-90,iHeight-190), true);
	velocity = guienv->addStaticText(L"velocity", rect<int>(10,iHeight-110,iWidth/2+35,iHeight), false);
	velocity->setOverrideFont(largeFont);

	targetBkg = guienv->addImage(vdriver->getTexture("res/menu/target_info.png"), core::position2d<s32>(iWidth-140,20));
	targetName = guienv->addStaticText(L"No Target Selected", rect<s32>(0,0,120,120), false, true, targetBkg);
}

void HUD::run()
{
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
}


//proected function
void HUD::updatePlayerInfo()
{
	core::stringw str(L"");
	str += (int)player->getInfo().velocity;
	str += L"m/s";
	velocity->setText(str.c_str());
}


void HUD::updateTargetInfo()
{
	const TargetableObject *target = player->getShipTarget();
	if(target)
	{
		//if a target exists
		targetName->setText(target->getName().c_str());
		//at this point we pull object information from this thing
	}
	else
	{
		//reset the text
		targetName->setText(L"No Target Selected");
	}
}
