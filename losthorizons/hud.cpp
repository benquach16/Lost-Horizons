#include "stdafx.h"
#include "hud.h"


//gunna have a huge initializer list here
HUD::HUD() : base(0), shipWheel(0)
{
	base = guienv->addWindow(rect<s32>(0,0,iWidth,iHeight), true);
	base->setDrawBackground(false);
	base->setDraggable(false);
	base->setDrawTitlebar(false);
	base->getCloseButton()->setVisible(false);
}

void HUD::initializeDisplay()
{

}

HUD::~HUD()
{
	base->remove();
}
