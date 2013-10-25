#include "stdafx.h"
#include "lensflare.h"
#include "globals.h"

using namespace base;

LensFlare::LensFlare(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : ISceneNode(parent, mgr, id)
{
	f32 shiftX, shiftY;
	shiftX = 0.5f/width;
	shiftY = 0.5f/height;  

	vertices[0] = video::S3DVertex2TCoords(
		-1.0f,-1.0f,0.0f,
		0.0f,0.0f,-1.0f,
		video::SColor(255,255,255,255),
		shiftX,1+shiftY,
		shiftX,1+shiftY);

	vertices[1] = video::S3DVertex2TCoords(
		1.0f,-1.0,0.0f,
		0.0f,0.0f,-1.0f,
		video::SColor(255,255,255,255),
		1.0f+shiftX,1+shiftY,
		1.0f+shiftX,1+shiftY);

	vertices[2] = video::S3DVertex2TCoords(
		-1.0f,1.0,0.0f,
		0.0f,0.0f,-1.0f,
		video::SColor(255,255,255,255),
		shiftX,shiftY,
		shiftX,shiftY);

	vertices[3] = video::S3DVertex2TCoords(
		1.0f,1.0f,0.0f,
		0.0f,0.0f,-1.0f,
		video::SColor(255,255,255,255),
		1.0f+shiftX,shiftY,
		1.0f+shiftX,shiftY);


	material.Lighting = false;                          
	material.BackfaceCulling=false;             
	material.MaterialType = video::EMT_LIGHTMAP_ADD; 
	setAutomaticCulling(scene::EAC_OFF);

	for(unsigned i = 0; i < 4; i++)
		box.addInternalPoint(vertices[i].Pos);
}

void LensFlare::render()
{
	video::IVideoDriver* drv = getSceneManager()->getVideoDriver();
	core::matrix4 proj;
	u16 indices[] = {0,1,2,3,1,2};
	drv->setMaterial(material);

	drv->setTransform(video::ETS_PROJECTION, core::IdentityMatrix);
	drv->setTransform(video::ETS_VIEW, core::IdentityMatrix);
	drv->setTransform(video::ETS_WORLD, core::IdentityMatrix);

	drv->drawIndexedTriangleList(&vertices[0],4,&indices[0],2);
}

void LensFlare::OnRegisterSceneNode()
{
	if(IsVisible && strength > 0)
		SceneManager->registerNodeForRendering(this, ESNRP_TRANSPARENT_EFFECT);
	ISceneNode::OnRegisterSceneNode();
}

const aabbox3df& LensFlare::getBoundingBox() const
{
	return box;
}

u32 LensFlare::getMaterialCount() const
{
	return 1;
}

video::SMaterial& LensFlare::getMaterial(u32 i) 
{
	return material;
}
