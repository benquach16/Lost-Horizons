#ifndef _SHIPTAB_H_
#define _SHIPTAB_H_

#include "menutab.h"

class ShipTab : public MenuTab
{
public:
	ShipTab(gui::IGUITabControl *tabs, Player* player);
	~ShipTab();

	void run();

private:
	Player* player;
};
#endif
