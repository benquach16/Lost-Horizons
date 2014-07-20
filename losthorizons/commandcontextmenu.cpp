#include "stdafx.h"
#include "globals.h"
#include "commandcontextmenu.h"

using namespace base;
using namespace irr;
using namespace core;
using namespace scene;

const wchar_t MOVELOCATION_STRING[] = L"Move to this location";
const wchar_t GENERALATTACK_STRING[] = L"Attack position";
const wchar_t ATTACKTARGET_STRING[] = L"Attack this target";
const wchar_t MOVEANDATTACK_STRING[] = L"Move here and Attack";
const wchar_t FOLLOW_STRING[] = L"Follow";
const wchar_t FOLLOW_PASSIVE_STRING[] = L"Follow (Passive)";

CommandContextMenu::CommandContextMenu()
{
	contextMenu = guienv->addContextMenu(rect<s32>(0,0,200,200));
	contextMenu->setCloseHandling(gui::ECONTEXT_MENU_CLOSE::ECMC_HIDE);
	//contextMenu->setItemAutoChecking(0, true);
	contextMenu->addItem(MOVELOCATION_STRING);
	contextMenu->addItem(GENERALATTACK_STRING);
	contextMenu->addItem(ATTACKTARGET_STRING);
	contextMenu->addItem(MOVEANDATTACK_STRING);
	contextMenu->addItem(FOLLOW_STRING);
	contextMenu->addItem(FOLLOW_PASSIVE_STRING);

	setVisible(false);
	
}

CommandContextMenu::~CommandContextMenu()
{
	contextMenu->remove();
}

void CommandContextMenu::run()
{
	int i = contextMenu->getSelectedItem();
	if(i != -1)
	{
		//do stuff
	}
}

void CommandContextMenu::setVisible(bool visible)
{
	contextMenu->setRelativePosition(position2di(receiver->getMouseX(),
		receiver->getMouseY()));
	contextMenu->setVisible(visible);
	if(visible)
	{
		guienv->setFocus(contextMenu);
	}
}

const bool CommandContextMenu::getVisible() const
{
	return contextMenu->isVisible();
}

const int CommandContextMenu::getSelected() const
{
	return contextMenu->getSelectedItem();
}
