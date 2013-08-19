#ifndef _PLANETPROPERTIES_H_
#define _PLANETPROPERTIES_H_

#include "modelproperties.h"

//planets
//each planet type has a different hardcoded value of production, index, etc
enum E_PLANET_TYPES
{
	E_PLANET_TERRAN,
	E_PLANET_GAS,
	E_PLANET_MOON,
	E_PLANET_BARREN,
	E_PLANET_ICE
};

class PlanetProperties : public ModelProperties
{
public:
	//default constructor
	PlanetProperties();
	//parameterized constructor
	PlanetProperties(irr::IrrlichtDevice *graphics, const std::string &f);
	~PlanetProperties();

protected:
	int maxPopulation;
	int maxDevelopmentIndex;
	int maxTechLevel;
};

#endif
