#ifndef _DESTRUCTIBLECOMPONENT_H_
#define _DESTRUCTIBLECOMPONENT_H_

#include "component.h"

namespace Component {

	class Destructible : public Component
	{
	public:
		// currently just a flag
		// or perhaps armor could be moved from health component to here
		// with entities lacking the destructible component having impervious armor
	};

}

#endif
