#ifndef _SHIPPROPERTIES_H_
#define _SHIPPROPERTIES_H_

#include "itemproperties.h"

//ship properties class
//all ships should be items

class ShipProperties : public ItemProperties
{
public:
	ShipProperties(IrrlichtDevice *graphics, const std::string &f);
	~ShipProperties();

private:
	int hull;
	int maxTurn;
	int maxVelocity;

	int maxEnergy;
	int maxCrew;

	int maxTurrets;
	int maxPDTurrets;
	int turretClass;	//1 light 2 medium 3 heavy
	int maxFighters;

	std::wstring filename;
	std::wstring diffuseMap;
	std::wstring normalMap;

	core::vector3df scale;
};

#endif
