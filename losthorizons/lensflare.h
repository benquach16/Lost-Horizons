#ifndef _LENSFLARE_H_
#define _LENSFLARE_H_

#include "stdafx.h"

using namespace irr;

//another constant effect
//a lens flare
//a lens flare node is another screen quad
class LensFlare : public scene::ISceneNode
{
public:
	LensFlare(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	virtual void render();
	virtual void OnRegisterSceneNode();
	virtual const core::aabbox3df& getBoundingBox() const;
	virtual u32 getMaterialCount() const;
	virtual video::SMaterial& getMaterial(u32 i);

	void setStrength(float newStrength)
	{
		strength = newStrength;
	}

protected:
	float strength;
	core::aabbox3d<f32> box;
	video::S3DVertex2TCoords vertices[4];
	video::SMaterial material;
};

#endif
