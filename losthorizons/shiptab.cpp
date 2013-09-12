#include "stdafx.h"
#include "shiptab.h"

ShipTab::ShipTab(IGUITab* ptr)
:shiptxt(NULL), description(NULL), subsystems(NULL), systems_list(NULL), 
 systems_health(NULL), crew_req(NULL), crew_avail(NULL), repair(NULL), replace(NULL)
{
	shiptxt = text(L"", 10, 20, iWidth - 10, 100, false, true, ptr);
	description = text(L"", 10, 60, iWidth - 10, 100, false, true, ptr);
	subsystems = text(L"Ship Subsystems", 10, 120, iWidth - 10, iHeight - 10, true, true, ptr);

}

ShipTab::~ShipTab()
{
}

void ShipTab::run()
{
}

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