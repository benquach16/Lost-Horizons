#include "stdafx.h"
#include "messagemenu.h"
#include "globals.h"

using namespace base;

MessageMenu::MessageMenu(const rect<s32> &rectangle, gui::IGUIElement *parent, const wchar_t *caption, unsigned flags, bool draggable, bool drawTitleBar, bool modal, s32 id)
	: MenuWindow(guienv->addWindow(rectangle, modal, caption, parent, id)),
	  value((MSGBOX_FLAG)(-1)), endTime(0), close(0), yes(0), no(0)
{
	//create window
	window->getCloseButton()->setVisible(false);
	window->setDraggable(draggable);
	window->setDrawTitlebar(drawTitleBar);
	window->setVisible(false);

	//create buttons
	if (flags % 2 == CLOSE) {
		close = guienv->addButton(rect<s32>(position2d<s32>(rectangle.getWidth()-17,4),dimension2d<s32>(14,14)), window, -1, L"x");
		if (!drawTitleBar)
			close->move(position2d<s32>(0,-2));
	}
	if (flags > CLOSE && flags < YESNO)
		yes = guienv->addButton(rect<s32>(position2d<s32>(rectangle.getWidth()/2-25,rectangle.getHeight()-50),dimension2d<s32>(50,30)), window, -1, L"OK");
	if (flags > OKAY) {
		yes = guienv->addButton(rect<s32>(position2d<s32>(-140,-50)+rectangle.getSize(),dimension2d<s32>(50,30)), window, -1, L"Yes");
		no = guienv->addButton(rect<s32>(position2d<s32>(-70,-50)+rectangle.getSize(),dimension2d<s32>(50,30)), window, -1, L"No");
	}
}

MessageMenu::~MessageMenu()
{
}

void MessageMenu::run()
{
	if (yes && yes->isPressed()) {
		window->setVisible(false);
		value = YES;
	}
	if (no && no->isPressed()) {
		window->setVisible(false);
		value = NO;
	}
	if (close && close->isPressed() || endTime > 0 && timer->getTime() > endTime) {
		window->setVisible(false);
	}
}

int MessageMenu::getSelected()
{
	return value;
}
