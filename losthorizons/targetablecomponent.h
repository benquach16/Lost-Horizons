#ifndef _TARGETABLECOMPONENT_H_
#define _TARGETABLECOMPONENT_H_

#include <vector>
#include "component.h"

namespace Component {

	class Targetable : public Component
	{
	public:
		bool showTarget;
		std::vector<unsigned> targettedByIDs;
	};

}

#endif
