#ifndef _SAVEMENU_H_
#define _SAVEMENU_H_

#include "menuwindow.h"

using namespace irr;
using namespace core;

class SaveMenu : public MenuWindow
{
public:

private:
	gui::IGUIButton *close;
	gui::IGUIButton *confirm;
};

#endif
