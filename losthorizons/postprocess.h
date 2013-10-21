#ifndef _POSTPROCESS_H_
#define _POSTPROCESS_H_

#include "stdafx.h"
#include "screenquadnode.h"

using namespace irr;

//postprocessing class
//does a render to texture to a screen quad
class PostProcessEffect
{
public:
	PostProcessEffect();
	~PostProcessEffect();
	void render();

protected:
	video::ITexture *renderTarget;
	video::ITexture *secondRenderTarget;
	video::ITexture *temp; 
	//first pass
	ScreenQuadNode *screenQuad;
	//second pass
	ScreenQuadNode *secondScreenQuad;

	//materials for shaders
	s32 shaderMaterial1;
	s32 shaderMaterial2;
	s32 shaderMaterial3;
};

#endif
