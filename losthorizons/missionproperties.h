#ifndef _MISSIONPROPERTIES_H_
#define _MISSIONPROPERTIES_H_

#include <string>

#include "irrlicht.h"

//for story missions or for cool missions we create
//not randomly generated
class MissionProperties
{
public:
	MissionProperties(irr::IrrlichtDevice *graphics, const std::string& f);
	~MissionProperties();
};

#endif
