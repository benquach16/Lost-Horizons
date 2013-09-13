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

//helper functions
private:
	//return pointers
	IGUIStaticText* text(wchar_t* name,
						 unsigned x1, unsigned y1, unsigned x2, unsigned y2,
						 bool border,
						 bool word_wrap,
						 IGUITab* ptr) const;
	IGUIListBox* list(unsigned x1, unsigned y1, unsigned x2, unsigned y2,
					  IGUITab* ptr) const;
	IGUIButton* button(unsigned x1, unsigned y1, unsigned x2, unsigned y2,
					   IGUITab* ptr,
					   s32 id,
					   const wchar_t* tmptxt) const;

};
#endif