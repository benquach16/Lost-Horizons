#include "stdafx.h"
#include "globals.h"
#include "commandcontextmenu.h"

using namespace base;
using namespace irr;
using namespace core;
using namespace scene;

CommandContextMenu::CommandContextMenu()
{
	contextMenu = guienv->addContextMenu(rect<s32>(0,0,300,500));
	contextMenu->addItem(L"Move to this location");
	contextMenu->addItem(L"General Attack");
	contextMenu->addItem(L"Attack this target");
	contextMenu->addItem(L"Move here and Attack");
	contextMenu->addItem(L"Follow");
	contextMenu->addItem(L"Follow (Passive)");
	setVisible(false);
	
}

CommandContextMenu::~CommandContextMenu()
{
}

void CommandContextMenu::run()
{

}

void CommandContextMenu::setVisible(bool visible)
{
	contextMenu->setRelativePosition(position2di(receiver->getMouseX(),
		receiver->getMouseY()));
	contextMenu->setVisible(visible);
}

const bool CommandContextMenu::getVisible() const
{
	return contextMenu->isVisible();
}
