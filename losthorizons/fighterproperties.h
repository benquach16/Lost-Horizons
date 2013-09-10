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
	const f32 getMaxTurn() const;
	const f32 getMaxVelocity() const;
	const unsigned getMaxFuel() const;
protected:
	int maxHull;
	f32 maxTurn;
	f32 maxVelocity;
	unsigned maxFuel;
};

#endif
