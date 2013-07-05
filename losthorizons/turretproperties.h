#ifndef _TURRETPROPERTIES_H_
#define _TURRETPROPERTIES_H_

#include "modelproperties.h"

//for turrets
class TurretProperties : public ModelProperties
{
public:
	//default constructor
	TurretProperties();
	//load from file
	TurretProperties(irr::IrrlichtDevice *graphics, const std::string &f);
	~TurretProperties();

	const int& getMaxTurn() const;
	const int& getDamage() const;
	const float& getReloadSpeed() const;
	const int& getRange() const;
protected:
	int turnSpeed;
	int damage;
	int range;
	float reloadSpeed;
};


#endif
