#include "stdafx.h"
#include "messagemenu.h"


MessageMenu::MessageMenu(const rect<s32> &rectangle, gui::IGUIElement *parent, const wchar_t *caption, unsigned flags, bool draggable, bool drawTitleBar, bool modal, s32 id)
	: MenuWindow(), close(0), yes(0), no(0)
{
	//create window
	window = guienv->addWindow(rectangle, modal, caption, parent, id);
	window->getCloseButton()->setVisible(false);
	window->setDraggable(draggable);
	window->setDrawTitlebar(drawTitleBar);

	//create buttons
	if (flags % 2 == CLOSE)
		close = guienv->addButton(rect<s32>(position2d<s32>(rectangle.getWidth()-17,4),dimension2d<s32>(14,14)), window, -1, L"x");
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

int MessageMenu::run()
{
	MenuWindow::run();
	if (getVisible()) {
		if (yes && yes->isPressed()) {
			setVisible(false);
			return YES;
		}
		if (no && no->isPressed()) {
			setVisible(false);
			return NO;
		}
		if (close && close->isPressed()) {
			setVisible(false);
		}
	}

	return 0;
}
