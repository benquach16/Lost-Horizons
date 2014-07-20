#ifndef _COMMANDCONTEXTMENU_H_
#define _COMMANDCONTEXTMENU_H_

#include <irrlicht.h>

class CommandContextMenu
{
public:
	CommandContextMenu();
	~CommandContextMenu();
	void run();
	void setVisible(bool visible);
	const bool getVisible() const;
	const int getSelected() const;
private:
	irr::gui::IGUIContextMenu *contextMenu;
};

#endif
