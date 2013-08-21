#include "stdafx.h"
#include "callback.h"
#include <iostream>

void BumpMapCallback::OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
{
	//set constants
	matrix4 projectionMatrix = services->getVideoDriver()->getTransform(video::ETS_PROJECTION);
	matrix4 viewMatrix = services->getVideoDriver()->getTransform(video::ETS_VIEW);
	matrix4 worldMatrix = services->getVideoDriver()->getTransform(video::ETS_WORLD);
	matrix4 projectionViewWorldMatrix = projectionMatrix*viewMatrix*worldMatrix;

	services->setVertexShaderConstant("World", worldMatrix.pointer(), 16);
	services->setVertexShaderConstant("matWorldViewProj", projectionViewWorldMatrix.pointer(), 16);

	f32 dir[4] = {1,0,0,0};
	services->setVertexShaderConstant("LightDirection", dir, 4);   
	 
	vector3df p = scenemngr->getActiveCamera()->getAbsolutePosition();
	f32 pos[4] = {p.X,p.Y,p.Z,0};
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

	f32 offsetX = -1.f/iWidth;
	f32 offsetY = 1.f/iHeight;
	f32 offset[2] = {offsetX, offsetY};
	//services->setVertexShaderConstant("Offset", offset, 2);
}

void PlanetCallback::OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
{
	IAnimatedMeshSceneNode *mesh = (IAnimatedMeshSceneNode*)userData;
	matrix4 projectionMatrix = services->getVideoDriver()->getTransform(video::ETS_PROJECTION);
	matrix4 viewMatrix = services->getVideoDriver()->getTransform(video::ETS_VIEW);
	matrix4 worldMatrix = services->getVideoDriver()->getTransform(video::ETS_WORLD);
	matrix4 projectionViewWorldMatrix = projectionMatrix*viewMatrix*worldMatrix;
	matrix4 inverseWorld = services->getVideoDriver()->getTransform(video::ETS_WORLD);
	inverseWorld.makeInverse();
	services->setVertexShaderConstant("matWorldViewProj", projectionViewWorldMatrix.pointer(), 16);
	services->setVertexShaderConstant("matWorldIT", inverseWorld.pointer(), 16);
	services->setVertexShaderConstant("matWorld", worldMatrix.pointer(), 16);
	vector3df p = scenemngr->getActiveCamera()->getAbsolutePosition();
	f32 pos[4] = {p.X,p.Y,p.Z,0};
	
	services->setVertexShaderConstant("vecViewPosition", pos, 4);

	f32 dir[3] = {1,0,0};
	services->setPixelShaderConstant("lightVec", dir, 3);   

	f32 col[3] = {255,200,255};
	//services->setPixelShaderConstant("lightCol", col, 3);   

}
