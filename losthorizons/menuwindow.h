#ifndef _MENUWINDOW_H_
#define _MENUWINDOW_H_

#include "stdafx.h"

using namespace irr;

//This is the base class of menus in the game

class MenuWindow
{
public:
	MenuWindow(gui::IGUIWindow *window = 0) : window(window) {}
	virtual ~MenuWindow()
	{
		if (window)
			window->remove();
	}

	virtual void run() = 0;

	void setVisible(bool visible)
	{
		window->setVisible(visible);
	}

	bool getVisible() const
	{
		return window->isVisible();
	}

protected:
	gui::IGUIWindow *window;
};
#endif
