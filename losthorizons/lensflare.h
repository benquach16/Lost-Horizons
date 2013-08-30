#ifndef _LENSFLARE_H_
#define _LENSFLARE_H_

#include "irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

//another constant effect
//a lens flare
//a lens flare node is another screen quad
class LensFlare : public ISceneNode
{
public:
	LensFlare(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	virtual void render();
	virtual void OnRegisterSceneNode();
	virtual const aabbox3df& getBoundingBox() const;
	virtual u32 getMaterialCount() const;
	virtual SMaterial& getMaterial(u32 i);

	void setStrength(float newStrength)
	{
		strength = newStrength;
	}

protected:
	float strength;
	aabbox3d<f32> box;
	S3DVertex2TCoords vertices[4];
	SMaterial material;
};

#endif
