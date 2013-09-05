#ifndef _HANGERTAB_H_
#define _HANGERTAB_H_

#include "menutab.h"

//class for the station refit menu
class HangerTab : public MenuTab
{
public:
	HangerTab(gui::IGUITabControl *tabs);
	~HangerTab();
	virtual void run();

protected:

};

#endif
