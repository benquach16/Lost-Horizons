#ifndef _VELOCITYCOMPONENT_H_
#define _VELOCITYCOMPONENT_H_

#include "component.h"
#include "irrlicht.h"

namespace Component {

	class Velocity : public Component
	{
	public:
		irr::f32 velocity;
		irr::f32 maxVelocity;
		irr::f32 maxTurn;
	};

}

#endif
