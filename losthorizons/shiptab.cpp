#include "stdafx.h"
#include "shiptab.h"

//PARAMETERIZED CONSTRUCTOR
ShipTab::ShipTab(IGUITab* ptr)
:shiptxt(NULL), description(NULL), subsystems(NULL), systems_list(NULL), 
 systems_health(NULL), crew_req(NULL), crew_avail(NULL), repair(NULL), replace(NULL)
{
	//creating
	shiptxt = text(L"", 10, 20, iWidth - 10, 100, false, true, ptr);
	description = text(L"", 10, 60, iWidth - 10, 100, false, true, ptr);
	subsystems = text(L"Ship Subsystems", 10, 120, iWidth - 10, iHeight - 10, true, true, ptr);
	systems_list = list(20, 140, (iWidth/2) - 10, iHeight - 20, ptr);
	systems_health = text(L"Integrity : ", iWidth / 2, 140, iHeight - 40, 220, false, true, ptr);
	crew_req = text(L"Crew Required : ",iWidth / 2, 200, iWidth - 40,220, false, true, ptr);
	crew_avail = text(L"Crew Available : ",iWidth / 2,170, iWidth - 40, 190, false, true, ptr);
	repair = button(iWidth - 240, iHeight - 60,iWidth - 140,iHeight - 40, ptr, -1,L"Repair");
	replace = button(iWidth - 120, iHeight - 60, iWidth - 20,iHeight - 40, ptr, -1,L"Replace");


	//initializing
	systems_list -> addItem(L"Bridge");
	systems_list -> addItem(L"Deck 1");
	systems_list -> addItem(L"Deck 2");
	systems_list -> addItem(L"Elevator");
	systems_list -> addItem(L"Engine");
	systems_list -> addItem(L"Warp Drive");
	systems_list -> addItem(L"Shield Module");
	systems_list -> addItem(L"Powerplant");
	systems_list -> addItem(L"Primary Weapon System");
	systems_list -> addItem(L"Secondary Weapon System");
	systems_list -> addItem(L"Light Weapon System");
}

//DESTRUCTOR
ShipTab::~ShipTab()
{
}

void ShipTab::run()
{
}

//HELPER FUNCTIONS
IGUIStaticText* ShipTab::text(wchar_t* name,
							  unsigned x1, unsigned y1, unsigned x2, unsigned y2,
							  bool border,
							  bool word_wrap,
							  IGUITab* ptr) const
{
	return guienv -> addStaticText(name, 
								   core::rect<s32>(x1, y1, x2, y2),
								   false,
					               true,
					               ptr);
}

IGUIListBox* ShipTab::list(unsigned x1, unsigned y1, unsigned x2, unsigned y2,
						   IGUITab* ptr) const
{
	return guienv -> addListBox(core::rect<s32>(x1, y1, x2, y2),
								ptr);

}

IGUIButton* ShipTab::button(unsigned x1, unsigned y1, unsigned x2, unsigned y2,
					   IGUITab* ptr,
					   s32 id,
					   const wchar_t* tmptxt) const
{
	return guienv -> addButton(core::rect<s32>(x1, y1, x2, y2),
							   ptr, 
							   id, 
							   tmptxt);
}