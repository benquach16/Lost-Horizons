#ifndef _SHIPTAB_H_
#define _SHIPTAB_H_

#include "menutab.h"


using namespace irr;
using namespace core;
using namespace gui;
using namespace scene;

class ShipTab : public MenuTab
{
//private member variables
private:
	//pointer declarations
	IGUIStaticText* shiptxt;
	IGUIStaticText* description;
	IGUIStaticText* subsystems;
	IGUIListBox* systems_list;
	IGUIStaticText* systems_health;
	IGUIStaticText* crew_req;
	IGUIStaticText* crew_avail;
	IGUIButton* repair;
	IGUIButton* replace;


public:
	//constructor
	ShipTab(IGUITab* ptr);
	~ShipTab();

	void run();
//helper function
private:
	//return pointer 
	IGUIStaticText* text(wchar_t* name,
						 unsigned x1, unsigned y1, unsigned x2, unsigned y2,
						 bool border,
						 bool word_wrap,
						 IGUITab* ptr) const;
};
#endif