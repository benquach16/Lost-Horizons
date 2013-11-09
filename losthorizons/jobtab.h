#ifndef _JOBTAB_H_
#define _JOBTAB_H_

#include "menutab.h"

//tab for job board
class JobTab : public MenuTab
{
public:
	JobTab(IGUITabControl *tabs);
	~JobTab();
	virtual void run();

private:

};

#endif
