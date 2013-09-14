#ifndef _OBJECTIVE_H_
#define _OBJECTIVE_H_

#include <string>

#include "irrlicht.h"

enum E_OBJECTIVE_TYPES
{
	E_OBJECTIVETYPE_SWEEP,
	E_OBJECTIVETYPE_COURIER,
	E_OBJECTIVETYPE_NAVIGATE,
	E_OBJECTIVETYPE_RETRIEVIAL,
	E_OBJECTIVETYPE_DEFEND
};

class Objective
{
public:
	Objective();
	~Objective();
	void run();
protected:
	std::wstring description;
	irr::core::vector3df position;
};

#endif
