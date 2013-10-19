#ifndef _OBJECTIVE_H_
#define _OBJECTIVE_H_

#include <string>

#include "irrlicht.h"
#include "ship.h"

using namespace irr;
using namespace core;

enum E_OBJECTIVE_TYPE
{
	OBJECTIVE_SWEEP,
	OBJECTIVE_COURIER,
	OBJECTIVE_NAVIGATE,
	OBJECTIVE_RETRIEVAL,
	OBJECTIVE_DEFEND
};

//objective class
//we run through the functions needed to check objective completeness
class Objective
{
public:
	Objective(const std::wstring &description, const E_OBJECTIVE_TYPE type, const vector3df& position, const unsigned radius);
	Objective(const E_OBJECTIVE_TYPE, const vector3df& position, const unsigned radius);
	~Objective();

	//run function
	//return true if player completed the objective
	bool run();
	const vector3df& getPosition() const;
protected:
	std::wstring description;
	E_OBJECTIVE_TYPE type;
	irr::core::vector3df position;
	unsigned radius;
};

#endif
