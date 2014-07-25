#ifndef _HEALTHCOMPONENT_H_
#define _HEALTHCOMPONENT_H_

#include "component.h"

class HealthComponent : public Component
{
public:
	HealthComponent();
	~HealthComponent();
protected:
	int hull;
	int armor;
	int shield;

	int maxHull;
	int maxArmor;
	int maxShield;
};

#endif
