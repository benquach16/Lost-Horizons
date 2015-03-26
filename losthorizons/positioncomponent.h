#ifndef _POSITIONCOMPONENT_H_
#define _POSITIONCOMPONENT_H_

#include "component.h"
#include "irrlicht.h"

namespace Component {

	class Position : public Component
	{
	public:
		irr::core::vector3df position;
		irr::core::vector3df rotation;
		irr::core::vector3df scale;
	};

}

#endif
