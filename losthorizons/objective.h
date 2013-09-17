#ifndef _OBJECTIVE_H_
#define _OBJECTIVE_H_

#include <string>

#include "irrlicht.h"

using namespace irr;
using namespace core;

enum E_OBJECTIVE_TYPES
{
	E_OBJECTIVETYPE_SWEEP,
	E_OBJECTIVETYPE_COURIER,
	E_OBJECTIVETYPE_NAVIGATE,
	E_OBJECTIVETYPE_RETRIEVAL,
	E_OBJECTIVETYPE_DEFEND
};

//objective class
//we run through the functions needed to check objective completeness
class Objective
{
public:
	Objective(const std::wstring &description, E_OBJECTIVE_TYPES objectiveType, const vector3df& position, const unsigned radius);
	~Objective();

	//run function
	//return true if player completed the objective
	bool run();
protected:
	std::wstring description;
	E_OBJECTIVE_TYPES objectiveType;
	irr::core::vector3df position;
	unsigned radius;
};

#endif
