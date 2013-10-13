#ifndef _MISSIONPROPERTIES_H_
#define _MISSIONPROPERTIES_H_

#include <string>

#include "irrlicht.h"
#include "objective.h"

using namespace irr;
using namespace io;

//for story missions or for cool missions we create
//not randomly generated
class MissionProperties
{
public:
	MissionProperties(irr::IrrlichtDevice *graphics, const std::string& f);
	~MissionProperties();

	const std::wstring& getName() const;
	const std::wstring& getDesc() const;
	const std::vector<Objective>& getObjs() const;
protected:
	E_OBJECTIVE_TYPE getObjectiveType(const wchar_t *text);
	std::wstring name;
	std::wstring description;
	unsigned numOfObjectives;
	std::vector<Objective> objectives;
};

#endif
