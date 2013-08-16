#include "stdafx.h"
#include "callback.h"


void BumpMapCallback::OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
{
	//set constants
	matrix4 projectionMatrix = services->getVideoDriver()->getTransform(video::ETS_PROJECTION);
	matrix4 viewMatrix = services->getVideoDriver()->getTransform(video::ETS_VIEW);
	matrix4 worldMatrix = services->getVideoDriver()->getTransform(video::ETS_WORLD);
	matrix4 projectionViewWorldMatrix = projectionMatrix*viewMatrix*worldMatrix;

	services->setVertexShaderConstant("World", worldMatrix.pointer(), 16);
	services->setVertexShaderConstant("matWorldViewProj", projectionViewWorldMatrix.pointer(), 16);

	float dir[4] = {1,0,0,0};
	services->setVertexShaderConstant("LightDirection", dir, 4);   
	 
	vector3df p = scenemngr->getActiveCamera()->getAbsolutePosition();
	float pos[4] = {p.X,p.Y,p.Z,0};
	services->setVertexShaderConstant("EyePosition", pos, 4);

	//f32 map = 1;
	//services->setPixelShaderConstant("usenmap", (f32*)&map, 1);
}

void BloomCallback::OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
{
	matrix4 projectionMatrix = services->getVideoDriver()->getTransform(video::ETS_PROJECTION);
	matrix4 viewMatrix = services->getVideoDriver()->getTransform(video::ETS_VIEW);
	matrix4 worldMatrix = services->getVideoDriver()->getTransform(video::ETS_WORLD);
	matrix4 projectionViewWorldMatrix = projectionMatrix*viewMatrix*worldMatrix;
	services->setVertexShaderConstant("matWorldViewProj", projectionViewWorldMatrix.pointer(), 16);

	float offsetX = -1/iWidth;
	float offsetY = 1 / iHeight;
	float offset[2] = {offsetX, offsetY};
	//services->setVertexShaderConstant("Offset", offset, 2);
}
