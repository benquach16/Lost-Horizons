#ifndef _SPACESTATIONPROPERTIES_H_
#define _SPACESTATIONPROPERTIES_H_

#include "modelproperties.h"

//space station xml loading
class SpaceStationProperties : public ModelProperties
{
public:
	SpaceStationProperties(irr::IrrlichtDevice *graphics, const std::string &f);
	~SpaceStationProperties();

protected:
};


#endif
