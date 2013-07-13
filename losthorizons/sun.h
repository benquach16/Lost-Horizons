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
	Sun(const vector3df &position, const vector3df &scale);

	//deconstructor
	~Sun();

protected:
	//light source
	irr::scene::ILightSceneNode *light;
};

#endif
