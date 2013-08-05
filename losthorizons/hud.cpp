#include "stdafx.h"
#include "hud.h"


//gunna have a huge initializer list here
HUD::HUD(Player *player) : shipWheel(0), player(player)
{
	//window = guienv->addGUIElement(gui::EGUIET_ELEMENT);
	initializeDisplay();
}

void HUD::initializeDisplay()
{
	IGUIFont *largeFont= guienv->getFont("res/font/verdana_large.xml");
	shipWheel = guienv->addImage(vdriver->getTexture("res/menu/hud.png"),core::position2d<s32>(-90,iHeight-190), true);
	velocity = guienv->addStaticText(L"velocity",rect<int>(10,iHeight-110,iWidth/2+35,iHeight),false);
	velocity->setOverrideFont(largeFont);
}

void HUD::run()
{
	updatePlayerInfo();
	
}

void HUD::setVisible(bool visible)
{
	//window->setVisible(visible);
	shipWheel->setVisible(visible);
	velocity->setVisible(visible);
}

HUD::~HUD()
{
	shipWheel->remove();
	velocity->remove();
}


//proected function
void HUD::updatePlayerInfo()
{
	int v = player->getInfo().velocity;
	core::stringw str(L"");
	str+=v;
	str+=L"m/s";
	velocity->setText(str.c_str());


}
