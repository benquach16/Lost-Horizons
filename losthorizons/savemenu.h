#ifndef _SAVEMENU_H_
#define _SAVEMENU_H_

#include "menuwindow.h"

using namespace irr;

class SaveMenu : public MenuWindow
{
public:
	SaveMenu(gui::IGUIWindow *menu);
	~SaveMenu();

private:
	gui::IGUIButton *close;
	gui::IGUIButton *confirm;
};

#endif
