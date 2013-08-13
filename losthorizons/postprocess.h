#ifndef _POSTPROCESS_H_
#define _POSTPROCESS_H_

#include "irrlicht.h"
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
	ScreenQuadNode *screenQuad;
};

#endif
