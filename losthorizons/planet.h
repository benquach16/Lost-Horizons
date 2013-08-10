#ifndef _PLANET_H_
#define _PLANET_H_

#include "object.h"
#include "targetableobject.h"
#include "planetproperties.h"



class Planet : public TargetableObject
{
public:
	//default constructor
	Planet();
	//parameterized constructor
	Planet(const E_PLANET_TYPES &type);
	~Planet();
	virtual void run();

protected:
	//planets have basic stats
	//different for each type of planet

	//affects production time
	int population;
	int maxPopulation;
	//how developed the planet is, ie number of factories and production facilities
	int developmentIndex;
	int maxDevelopmentIndex;
	//tech level of the planet
	int techIndex;
	int maxTechLevel;


	

};


#endif
