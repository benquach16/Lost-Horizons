#ifndef _INTERCOM_H_
#define _INTERCOM_H_

#include "stdafx.h"

using namespace irr;

//doesn't do anything useful but provides immersion value
//essentially just provides text updates from the crew and from
//faction headquarters
//functions as a crew intercom 
class Intercom
{
public:
	Intercom();
	~Intercom();

	void run();
	void postMessage(const wchar_t *text);

private:
	gui::IGUIListBox *listBox;
	//have different tabs to organize comms
	gui::IGUITabControl *tabs;
	gui::IGUITab *ship;
	gui::IGUITab *external;

	unsigned lastPosted, endTime;
};

#endif
