#ifndef _HEALTHCOMPONENT_H_
#define _HEALTHCOMPONENT_H_

#include "component.h"

namespace Component {

	class Health : public Component
	{
	public:
		int hull;
		int maxHull;

		int armor;
		int maxArmor;
	};

}

#endif
