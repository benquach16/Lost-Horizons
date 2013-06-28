#include "stdafx.h"
#include "messagemenu.h"


MessageMenu::MessageMenu(const rect<s32> &rectangle, const wchar_t *caption, FLAGS flags, gui::IGUIElement *parent, bool modal, s32 id)
	: MenuWindow(), close(0), yes(0), no(0), UpperLeft(rectangle.UpperLeftCorner), LowerRight(rectangle.LowerRightCorner)
{
	//create window
	window = guienv->addWindow(rectangle, modal, caption, parent, id);
	window->getCloseButton()->setVisible(false);

	//create buttons
	if (flags % 2 == MM_CLOSE)
		close = guienv->addButton(rect<s32>(UpperLeft+rectangle.getWidth()+position2d<s32>(-15,5),dimension2d<s32>(10,10)), window, -1, L"x");
	if (flags > MM_CLOSE && flags < MM_YESNO)
		yes = guienv->addButton(rect<s32>(LowerRight-position2d<s32>(rectangle.getWidth()/2+25,50),dimension2d<s32>(50,30)), window, -1, L"OK");
	if (flags > MM_OKAY) {
		yes = guienv->addButton(rect<s32>(LowerRight-position2d<s32>(140,50),dimension2d<s32>(50,30)), window, -1, L"Yes");
		no = guienv->addButton(rect<s32>(LowerRight-position2d<s32>(70,50),dimension2d<s32>(50,30)), window, -1, L"No");
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
			return MM_YES;
		}
		if (no && no->isPressed()) {
			setVisible(false);
			return MM_NO;
		}
		if (close && close->isPressed()) {
			setVisible(false);
		}
	}

	return 0;
}
