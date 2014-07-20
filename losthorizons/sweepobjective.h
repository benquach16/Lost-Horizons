#ifndef _SWEEPOBJECTIVE_H_
#define _SWEEPOBJECTIVE_H_

#include "objective.h"

//Begin polymorphic definitions of objectives
class SweepObjective : public Objective
{
public:

	SweepObjective(const std::wstring &description, const vector3df &position);
	SweepObjective(const vector3df &position);
	virtual ~SweepObjective();
	virtual bool run();
	virtual const E_OBJECTIVE_TYPE getObjectiveType() const;

protected:

};

#endif
