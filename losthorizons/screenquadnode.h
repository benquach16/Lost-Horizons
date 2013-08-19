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
		
		f32 shiftX,shiftY;
        shiftX = (f32)0.5/iWidth;
        shiftY = (f32)0.5/iHeight;  
 
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
			
		/*
		vertices[0] = irr::video::S3DVertex(-1.0f,-1.0f,0.0f,0,0,1,irr::video::SColor(0x0),0.0f,1.0f);
		vertices[1] = irr::video::S3DVertex(-1.0f, 1.0f,0.0f,0,0,1,irr::video::SColor(0x0),0.0f,0.0f);
		vertices[2] = irr::video::S3DVertex( 1.0f, 1.0f,0.0f,0,0,1,irr::video::SColor(0x0),1.0f,0.0f);
		vertices[3] = irr::video::S3DVertex( 1.0f,-1.0f,0.0f,0,0,1,irr::video::SColor(0x0),1.0f,1.0f);
		vertices[4] = irr::video::S3DVertex(-1.0f,-1.0f,0.0f,0,0,1,irr::video::SColor(0x0),0.0f,1.0f);
		vertices[5] = irr::video::S3DVertex( 1.0f, 1.0f,0.0f,0,0,1,irr::video::SColor(0x0),1.0f,0.0f);
		*/

		material.Lighting = false;                          
		material.BackfaceCulling=false;             
		material.Wireframe =false;

		box.reset(vertices[0].Pos);
        
        for(unsigned i = 0; i < 4; i++)
			box.addInternalPoint(vertices[i].Pos);
	}
    void render()
    {
		video::IVideoDriver* drv = getSceneManager()->getVideoDriver();
		core::matrix4 proj;
		u16 indices[] = {0,1,2,3,1,2};
		//u16 indices[6] = {0, 2, 3,   0, 1, 2};
		//irr::u16 indices[6] = {0, 1, 2, 3, 4, 5};
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
			SceneManager->registerNodeForRendering(this, scene::ESNRP_TRANSPARENT);
		}
		ISceneNode::OnRegisterSceneNode();
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
