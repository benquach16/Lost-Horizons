#ifndef _PLANETPROPERTIES_H_
#define _PLANETPROPERTIES_H_

#include "modelproperties.h"

//planets
//each planet type has a different hardcoded value of production, index, etc
enum E_PLANET_TYPE
{
	PLANET_TERRAN,
	PLANET_GAS,
	PLANET_MOON,
	PLANET_BARREN,
	PLANET_ICE
};

class PlanetProperties : public ModelProperties
{
public:
	PlanetProperties(const std::string &f);
	~PlanetProperties();

	const wchar_t *getCloudMap() const;

protected:
	std::wstring cloudMap;
	int maxPopulation;
	int maxDevelopmentIndex;
	int maxTechLevel;
};

#endif
