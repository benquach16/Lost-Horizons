#ifndef _SCREENQUADNODE_H_
#define _SCREENQUADNODE_H_

#include "irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
//custom scenenode
//screen aligned quad for postprocessing
class ScreenQuadNode : public ISceneNode
{
public:
	ScreenQuadNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : ISceneNode(parent, mgr, id)
	{

		box.reset(0,0,0);


		vertices[0] = video::S3DVertex2TCoords(
			-1.0f,-1.0f,0.0f,
			0.0f,0.0f,-1.0f,
			video::SColor(255,255,255,255),
			0.0,1,
			0.0,1);

		vertices[1] = video::S3DVertex2TCoords(
			1.0f,-1.0,0.0f,
			0.0f,0.0f,-1.0f,
			video::SColor(255,255,255,255),
			1.0f,1,
			1.0f,1);

		vertices[2] = video::S3DVertex2TCoords(
			-1.0f,1.0,0.0f,
			0.0f,0.0f,-1.0f,
			video::SColor(255,255,255,255),
			0.0,0.0,
			0.0,0.0);

		vertices[3] = video::S3DVertex2TCoords(
			1.0f,1.0f,0.0f,
			0.0f,0.0f,-1.0f,
			video::SColor(255,255,255,255),
			1.0f,0.0,
			1.0f,0.0);



		material.Lighting = false;                          
		material.MaterialType = video::EMT_LIGHTMAP_ADD;   
		material.BackfaceCulling=false;             
		setAutomaticCulling(scene::EAC_OFF);      
	}
    void render()
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
    virtual void OnRegisterSceneNode()
    {

    }
    virtual const aabbox3d<f32>& getBoundingBox() const
    {
        return box;
    }
    virtual u32 getMaterialCount() const
    {
        return 1;
    }
    virtual SMaterial& getMaterial(u32 i)
    {
        return material;
    }  

protected:
	//store baux
	aabbox3d<f32> box;
	S3DVertex2TCoords vertices[4];
	SMaterial material;

};

#endif
