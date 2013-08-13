#include "stdafx.h"
#include "postprocess.h"

PostProcessEffect::PostProcessEffect() : screenQuad(new ScreenQuadNode(scenemngr->getRootSceneNode(), scenemngr, 10))
{
	//create screen aligned quad and set the render to texture
	ITexture *renderTarget;
}

void PostProcessEffect::render()
{
}
