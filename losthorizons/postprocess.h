#ifndef _POSTPROCESS_H_
#define _POSTPROCESS_H_

#include "irrlicht.h"

using namespace irr;

//postprocessing class
//does a render to texture to a screen quad
class PostProcessEffect
{
public:
	PostProcessEffect();
	~PostProcessEffect();
	void render(video::ITexture *renderTarget);
};

#endif
