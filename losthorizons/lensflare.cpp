#include "lensflare.h"

LensFlare::LensFlare(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : ISceneNode(parent, mgr, id)
{
}

void LensFlare::render()
{
}

void LensFlare::OnRegisterSceneNode()
{
}

const aabbox3df& LensFlare::getBoundingBox() const
{
	return box;
}

u32 LensFlare::getMaterialCount() const
{
	return 1;
}

SMaterial& LensFlare::getMaterial(u32 i) 
{
	return material;
}
