#ifndef _PLANET_H_
#define _PLANET_H_

#include "object.h"
#include "targetableobject.h"
#include "planetproperties.h"
#include "atmosphere.h"


//planet class
class Planet : public TargetableObject
{
public:
	//parameterized constructor
	Planet(ObjectManager::E_PLANET_LIST pleantType, const vector3df &position);
	~Planet();
	virtual void run();

	const virtual E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const;

protected:
	scene::IAnimatedMeshSceneNode *cloudMesh;
	//scene::IBillboardSceneNode *atmosphere;
	Atmosphere *atmosphere;
	//protected function
	//does as described
	void enablePlanetShader();
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
