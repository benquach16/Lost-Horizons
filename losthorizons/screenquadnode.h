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
		material.Lighting = false;
        vertices[0] = S3DVertex(vector3df(-1.0f, 1.0f, 0.0f), vector3df(), SColor(255,0,0,0), vector2df(0.0f, 0.0f));
        vertices[1] = S3DVertex(vector3df(1.0f, 1.0f, 0.0f), vector3df(), SColor(255,0,0,0), vector2df(1.0f, 0.0f));
        vertices[2] = S3DVertex(vector3df(1.0f, -1.0f, 0.0f), vector3df(), SColor(255,0,0,0), vector2df(1.0f, 1.0f));
        vertices[3] = S3DVertex(vector3df(-1.0f, -1.0f, 0.0f), vector3df(), SColor(255,0,0,0), vector2df(0.0f, 1.0f));

		box.reset(vertices[0].Pos);
		for(unsigned i = 1; i < 4; i++)
		{
			box.addInternalPoint(vertices[i].Pos);
		}
	}
    void render()
    {
        u16 indices[6] = {0, 2, 3,   0, 1, 2};
        IVideoDriver* driver = SceneManager->getVideoDriver();
        driver->setMaterial(material);
        driver->setTransform(ETS_WORLD, AbsoluteTransformation);
        driver->drawIndexedTriangleList(&vertices[0], 4, &indices[0], 2);
    }
    virtual void OnRegisterSceneNode()
    {
        if (IsVisible)
            SceneManager->registerNodeForRendering(this);
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
	S3DVertex vertices[4];
	SMaterial material;

};

#endif
