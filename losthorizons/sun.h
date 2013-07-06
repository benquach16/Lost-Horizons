#ifndef _SUN_H_
#define _SUN_H_

#include "object.h"

//just a sun
//its really just an object with a couple of other parameters
class Sun : public Object
{
public:

	//default constructor
	Sun();

	//parameterized constructor
	Sun(irr::IrrlichtDevice *graphics, const vector3df &position = vector3df(1,1,1), const vector3df &scale = vector3df(1,1,1));

	//deconstructor
	~Sun();

protected:
	//light source
	irr::scene::ILightSceneNode *light;
};

#endif
