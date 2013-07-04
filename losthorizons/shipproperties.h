#ifndef _SHIPPROPERTIES_H_
#define _SHIPPROPERTIES_H_

#include "modelproperties.h"

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
	const float& getMaxVel() const;

	const int& getMaxEnergy() const;
	const int& getMaxCrew() const;

	const int& getMaxLTurrets() const;
	const int& getMaxMTurrets() const;
	const int& getMaxHTurrets() const;
	const int& getMaxPTurrets() const;


	
protected:
	//performance statistics
	int hull;
	int maxTurn;
	float maxVelocity;

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
