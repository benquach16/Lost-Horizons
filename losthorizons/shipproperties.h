#ifndef _SHIPPROPERTIES_H_
#define _SHIPPROPERTIES_H_

#include "modelproperties.h"
#include <vector>


struct turretInformation
{
	core::vector3df rotation;
	int arc;
	//for empty turret infos
	turretInformation() : rotation(), arc(360){}
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

	//accessors because visual studio
	const int& getMaxHull() const;
	const int& getMaxArmor() const;
	const int& getMaxShield() const;
	const int& getMaxTurn() const;
	const f32& getMaxVel() const;
	const int& getMaxCargo() const;
	const int& getNumEngines() const;

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
	int maxHull;
	int maxArmor;
	int maxShield;
	int maxTurn;
	f32 maxVelocity;
	int maxCargo;
	int numEngines;

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
