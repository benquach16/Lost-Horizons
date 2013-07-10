#ifndef _PLANET_H_
#define _PLANET_H_

#include "object.h"

//planets
enum E_PLANET_TYPES
{
	E_PLANET_TERRAN,
	E_PLANET_GAS,
	E_PLANET_MOON,
	E_PLANET_BARREN,
	E_PLANET_ICE
};

class Planet : public Object
{
public:
	Planet();
	Planet(irr::IrrlichtDevice *graphics);
	~Planet();
	virtual void run();

protected:
	//planets have basic stats
	//different for each type of planet

	//affects production time
	int population;
	//how developed the planet is, ie number of factories and production facilities
	int developmentIndex;
	//tech level of the planet
	int techIndex;

	

};


#endif
