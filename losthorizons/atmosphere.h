#ifndef _ATMOSPHERE_H_
#define _ATMOSPHERE_H_

#include "stdafx.h"

using namespace irr;

//this is an atmosphere special effect because atmospheric scattering shaders are hard

class Atmosphere
{
public:
	Atmosphere(const core::vector3df& position);
	~Atmosphere();
	void run();

protected:
	scene::ISceneNode *atmosphereSceneNode;
};

#endif
