#ifndef _VISIBLECOMPONENT_H_
#define _VISIBLECOMPONENT_H_

#include "component.h"
#include "irrlicht.h"

namespace Component {

	class Visible : public Component
	{
	public:
		irr::scene::IAnimatedMeshSceneNode *mesh;
	};

}

#endif
