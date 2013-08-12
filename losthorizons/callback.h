#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include "irrlicht.h"

//we create a class to pass information to a shader
using namespace irr;
using namespace core;

class BumpMapCallback : public video::IShaderConstantSetCallBack
{
public:
	float lightDirection[4];
	virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData);
};


#endif
