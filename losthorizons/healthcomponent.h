#ifndef _HEALTHCOMPONENT_H_
#define _HEALTHCOMPONENT_H_

#include "component.h"

namespace Component {

	class Health : public Component
	{
	public:
		int hull;
		int armor;
		//int shield; // to be moved to shield component

		int maxHull;
		int maxArmor;
		//int maxShield;
	};

}

#endif
