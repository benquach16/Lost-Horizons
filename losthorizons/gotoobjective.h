#ifndef _GOTOOBJECTIVE_H_
#define _GOTOOBJECTIVE_H_

#include "objective.h"

class GotoObjective : public Objective
{
public:
	GotoObjective(const std::wstring& description, const irr::core::vector3df& position);
	GotoObjective(const vector3df& position);
	~GotoObjective();

	virtual bool run();
	virtual const E_OBJECTIVE_TYPE getObjectiveType() const;

protected:

};

#endif
