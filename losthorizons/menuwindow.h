#ifndef _MENUWINDOW_H_
#define _MENUWINDOW_H_

#include "stdafx.h"

using namespace irr;

//This is the base class of menus in the game

class MenuWindow
{
public:
	MenuWindow() : window(0), visible(false) {}
	virtual ~MenuWindow()
	{
		if (window)
			window->remove();
	}

	void run()
	{
		window->setVisible(visible);
	}

	void setVisible(bool show)
	{
		visible = show;
	}

	bool getVisible()
	{
		return visible;
	}

private:
	bool visible;

protected:
	gui::IGUIWindow *window;
};
#endif
