#include "stdafx.h"
#include "hud.h"


//gunna have a huge initializer list here
HUD::HUD() : shipWheel(0)
{
	window = guienv->addWindow(rect<s32>(0,0,iWidth,iHeight), true);
	window->setDrawBackground(false);
	window->setDraggable(false);
	window->setDrawTitlebar(false);
	window->getCloseButton()->setVisible(false);
	initializeDisplay();
}

void HUD::initializeDisplay()
{
	shipWheel = guienv->addImage(vdriver->getTexture("res/menu/hud.png"),core::position2d<s32>(-90,iHeight-190), true, window);
}

void HUD::run(Object *playerTarget)
{

}

void HUD::setVisible(bool visible)
{
	window->setVisible(visible);
}

HUD::~HUD()
{
}
