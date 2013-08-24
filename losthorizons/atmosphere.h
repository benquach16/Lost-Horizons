#ifndef _ATMOSPHERE_H_
#define _ATMOSPHERE_H_

//this is an atmosphere special effect because atmospheric scattering shaders are hard


#include "irrlicht.h"


using namespace irr;
using namespace core;

class Atmosphere
{
public:
	Atmosphere(const vector3df& position);
	~Atmosphere();
	void run();

protected:
	ISceneNode *atmosphereSceneNode;

};

#endif
