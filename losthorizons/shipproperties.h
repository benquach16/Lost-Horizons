#ifndef _SHIPPROPERTIES_H_
#define _SHIPPROPERTIES_H_

#include "modelproperties.h"
#include <vector>


struct turretInformation
{
	core::vector3df rotation;
	int arc;
};

//ship properties class
//all ships should be items

class ShipProperties : public ModelProperties
{
public:


	//default constructor
	ShipProperties();
	ShipProperties(IrrlichtDevice *graphics, const std::string &f);
	~ShipProperties();

	//accessors because visual studio is a douchebag
	const int& getHull() const;
	const int& getMaxTurn() const;
	const f32& getMaxVel() const;

	const int& getMaxEnergy() const;
	const int& getMaxCrew() const;

	const int& getMaxLTurrets() const;
	const int& getMaxMTurrets() const;
	const int& getMaxHTurrets() const;
	const int& getMaxPTurrets() const;

	const int& getMaxFighters() const;

	std::vector<turretInformation> heavyTurrets;
	std::vector<turretInformation> mediumTurrets;	
	std::vector<turretInformation> lightTurrets;

	
protected:
	void loadTurretInformation(io::IXMLReader *file);

	//performance statistics
	int hull;
	int maxTurn;
	f32 maxVelocity;

	//logistic statistics
	int maxEnergy;
	int maxCrew;

	//combat statistics
	int maxLightTurrets;
	int maxMediumTurrets;
	int maxHeavyTurrets;
	int maxPDTurrets;
	int maxFighters;

};

#endif
