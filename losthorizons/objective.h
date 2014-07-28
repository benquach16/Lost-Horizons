#ifndef _OBJECTIVE_H_
#define _OBJECTIVE_H_


#include "stdafx.h"
#include "ship.h"
#include <string>

using namespace irr;

enum E_OBJECTIVE_TYPE
{
	OBJECTIVE_SWEEP,
	OBJECTIVE_COURIER,
	OBJECTIVE_NAVIGATE,
	OBJECTIVE_RETRIEVAL,
	OBJECTIVE_DEFEND,
	OBJECTIVE_DESTROY_SPECIFIC
};

enum E_OBJECTIVE_STATE
{
	OBJECTIVE_STATE_FINISHED,
	OBJECTIVE_STATE_INPROGRESS,
	OBJECTIVE_STATE_FAILED
};

//objective class
//we run through the functions needed to check objective completeness
//TODO: MAKE THIS AN ABSTRACT CLASS
class Objective
{
public:
	Objective(const std::wstring &description, const vector3df& position);
	Objective(const vector3df& position);
	virtual ~Objective();

	//run function
	//return true if player completed the objective
	virtual bool run();
	const vector3df& getPosition() const;
	virtual const E_OBJECTIVE_TYPE getObjectiveType() const;
	const std::wstring& getDescription() const;
protected:
	std::wstring description;
	E_OBJECTIVE_STATE state;
	E_OBJECTIVE_TYPE type;
	vector3df position;
	unsigned timeKeeping;
};

#endif
