#ifndef _SHIELDCOMPONENT_H_
#define _SHIELDCOMPONENT_H_

#include "component.h"

namespace Component {

	class Shield : public Component
	{
	public:
		int shield;
		int maxShield;

		//add shield regen data?
	};

}

#endif
