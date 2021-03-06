#ifndef _SCREENQUADNODE_H_
#define _SCREENQUADNODE_H_

#include "globals.h"

using namespace irr;
using namespace base;

//custom scenenode
//screen aligned quad for postprocessing
class ScreenQuadNode : public scene::ISceneNode
{
public:
	ScreenQuadNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : ISceneNode(parent, mgr, id)
	{
		
		f32 shiftX, shiftY;
        shiftX = 0.5f/width;
        shiftY = 0.5f/height;  
		box.reset(0,0,0);
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
		  material.ZBuffer = video::ECFN_ALWAYS;
		material.ZWriteEnable = false;
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
		if(IsVisible)
		{
			SceneManager->registerNodeForRendering(this, scene::ESNRP_TRANSPARENT_EFFECT);
		}
		ISceneNode::OnRegisterSceneNode();
	}
    const core::aabbox3d<f32>& getBoundingBox() const
    {
        return box;
    }
    virtual u32 getMaterialCount() const
    {
        return 1;
    }
    virtual video::SMaterial& getMaterial(u32 i)
    {
        return material;
    }  

protected:
	//store baux
	core::aabbox3d<f32> box;
	video::S3DVertex2TCoords vertices[4];
	video::SMaterial material;

};

#endif
