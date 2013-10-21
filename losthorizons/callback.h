#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include "stdafx.h"
using namespace irr;

//we create a class to pass information to a shader

class BumpMapCallback : public video::IShaderConstantSetCallBack
{
public:
	virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData);
};

class BloomCallback : public video::IShaderConstantSetCallBack
{
public:
	virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData);
};

class PlanetCallback : public video::IShaderConstantSetCallBack
{
public:
	virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData);
};

#endif
