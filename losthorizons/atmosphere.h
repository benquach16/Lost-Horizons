#ifndef _ATMOSPHERE_H_
#define _ATMOSPHERE_H_

//this is an atmosphere special effect because atmospheric scattering shaders are hard


#include "irrlicht.h"

using namespace irr;

class Atmosphere
{
public:
	Atmosphere();
	~Atmosphere();

	virtual void run(f32 frameDeltaTime);
};

#endif
