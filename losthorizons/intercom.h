#ifndef _INTERCOM_H_
#define _INTERCOM_H_

#include "player.h"

//doesn't do anything useful but provides immersion value
//essentially just provides text updates from the crew and from
//faction headquarters
//functions as a crew intercom 
class Intercom
{
public:
	Intercom(Player *player);
	~Intercom();

	void run();

private:
	Player *player;
	gui::IGUIListBox *listBox;
	//have different tabs to organize comms
	gui::IGUITabControl *tabs;
	gui::IGUITab *ship;
	gui::IGUITab *external;
};

#endif
