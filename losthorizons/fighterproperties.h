#ifndef _FIGHTERPROPERTIES_H_
#define _FIGHTERPROPERTIES_H_

#include "modelproperties.h"

//fighter properties class
class FighterProperties : public ModelProperties
{
public:
	//default constructor
	FighterProperties();
	FighterProperties(irr::IrrlichtDevice *graphics, const std::string &f);
	virtual ~FighterProperties();
	//accessors
	const int getMaxHull() const;
	const int getMaxTurn() const;
	const int getMaxVelocity() const;
	const unsigned getMaxFuel() const;
protected:
	int maxHull;
	int maxTurn;
	int maxVelocity;
	unsigned maxFuel;
};

#endif
