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

	//accessors because visual studio is a douchebag
	const int& getHull() const;
	const int& getMaxTurn() const;
	const int& getMaxVel() const;

	const int& getMaxEnergy() const;
	const int& getMaxCrew() const;

	const int& getMaxLTurrets() const;
	const int& getMaxMTurrets() const;
	const int& getMaxHTurrets() const;
	const int& getMaxPTurrets() const;

	const std::wstring& getFilename() const;
	const std::wstring& getDiffuseMap() const;
	const std::wstring& getNormalMap() const;

	const core::vector3df& getScale() const;
	
protected:
	//performance statistics
	int hull;
	int maxTurn;
	int maxVelocity;

	//logistic statistics
	int maxEnergy;
	int maxCrew;

	//combat statistics
	int maxLightTurrets;
	int maxMediumTurrets;
	int maxHeavyTurrets;
	int maxPDTurrets;
	int maxFighters;

	//model information
	std::wstring filename;
	std::wstring diffuseMap;
	std::wstring normalMap;

	core::vector3df scale;
};

#endif
