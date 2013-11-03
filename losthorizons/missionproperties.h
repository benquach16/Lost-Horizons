#ifndef _MISSIONPROPERTIES_H_
#define _MISSIONPROPERTIES_H_

#include <string>
#include "objective.h"

//for story missions or for cool missions we create
//not randomly generated
class MissionProperties
{
public:
	MissionProperties(const std::string& f);
	~MissionProperties();

	const wchar_t *getName() const;
	const wchar_t *getDesc() const;
	const std::vector<Objective>& getObjs() const;

protected:
	E_OBJECTIVE_TYPE getObjectiveType(const wchar_t *text);
	std::wstring name;
	std::wstring description;
	unsigned numOfObjectives;
	std::vector<Objective> objectives;
};

#endif
