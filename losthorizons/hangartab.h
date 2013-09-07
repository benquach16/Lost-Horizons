#ifndef _HANGARTAB_H_
#define _HANGARTAB_H_

#include "menutab.h"

//class for the station refit menu
class HangarTab : public MenuTab
{
public:
	HangarTab(gui::IGUITabControl *tabs);
	~HangarTab();
	virtual void run();

protected:

};

#endif
