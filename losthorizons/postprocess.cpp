#include "stdafx.h"
#include "postprocess.h"

PostProcessEffect::PostProcessEffect() : screenQuad(new ScreenQuadNode(scenemngr->getRootSceneNode(), scenemngr, 10)),
	secondScreenQuad(new ScreenQuadNode(scenemngr->getRootSceneNode(), scenemngr, 11))
{

	//create screen aligned quad and set the render to texture
	//keep in mind we need to do two passes for proper bloom!
	renderTarget = vdriver->addRenderTargetTexture(dimension2du(iWidth, iHeight), "renderTarget");
	secondRenderTarget = vdriver->addRenderTargetTexture(dimension2du(iWidth, iHeight), "secondRenderTarget");
	screenQuad->setMaterialTexture(0, renderTarget);
	//in order to set up multiple render passes, we need multiple render targets so we can draw the first pass
	//and the second pass, then merge them
	BloomCallback *bp = new BloomCallback;
	s32 shadermat1 = vdriver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles("shaders/bloom.hlsl", "VertexShaderFunction",
		video::EVST_VS_3_0, "shaders/bloom.hlsl", "PixelShaderFunction", video::EPST_PS_3_0, bp, video::EMT_SOLID);
	screenQuad->setMaterialType((video::E_MATERIAL_TYPE)shadermat1);
	secondScreenQuad->setMaterialTexture(0, renderTarget);
	secondScreenQuad->setMaterialTexture(1, secondRenderTarget);
	s32 shadermat2 = vdriver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles("shaders/blur.hlsl", "VertexShaderFunction",
		video::EVST_VS_3_0, "shaders/blur.hlsl", "PixelShaderFunction", video::EPST_PS_3_0, bp, video::EMT_SOLID);
	//secondScreenQuad->setMaterialType((video::E_MATERIAL_TYPE)shadermat2);
	bp->drop();
}

void PostProcessEffect::render()
{


	vdriver->setRenderTarget(renderTarget,true, true, video::SColor(0,0,0,255));
	scenemngr->drawAll();
	vdriver->setRenderTarget(secondRenderTarget, true, true, video::SColor(0,0,0,255));

	vdriver->draw2DImage(renderTarget, rect<s32>(0,0,iWidth, iHeight), rect<s32>(0,0,iWidth, iHeight));

	vdriver->setRenderTarget(video::ERT_FRAME_BUFFER, true, true);
	screenQuad->render();
	secondScreenQuad->render();
	
}
