#include "stdafx.h"
#include "postprocess.h"
#include "globals.h"

using namespace base;

PostProcessEffect::PostProcessEffect() :
	screenQuad(new ScreenQuadNode(scenemngr->getRootSceneNode(), scenemngr, -1))
	//secondScreenQuad(new ScreenQuadNode(scenemngr->getRootSceneNode(), scenemngr, 11))
{

	//create screen aligned quad and set the render to texture
	//keep in mind we need to do two passes for proper bloom!
	renderTarget = vdriver->addRenderTargetTexture(dimension2du(width, height), "renderTarget");
	secondRenderTarget = vdriver->addRenderTargetTexture(dimension2du(width, height), "secondRenderTarget");
	screenQuad->setMaterialTexture(0, renderTarget);
	screenQuad->setMaterialTexture(1, secondRenderTarget);
	//screenQuad->getMaterial(0).setTexture(0, renderTarget);
	//screenQuad->getMaterial(0).setTexture(1, secondRenderTarget);
	//in order to set up multiple render passes, we need multiple render targets so we can draw the first pass
	//and the second pass, then merge them
	BloomCallback *bp = new BloomCallback;
	shaderMaterial1 = vdriver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles("shaders/bloom.hlsl", "VertexShaderFunction",
		video::EVST_VS_3_0, "shaders/bloom.hlsl", "PixelShaderFunction", video::EPST_PS_3_0, bp, video::EMT_SOLID);
	//screenQuad->setMaterialType((video::E_MATERIAL_TYPE)shaderMaterial1);
	//secondScreenQuad->setMaterialTexture(0, renderTarget);
	//secondScreenQuad->setMaterialTexture(1, secondRenderTarget);
	shaderMaterial2 = vdriver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles("shaders/blur.hlsl", "VertexShaderFunction",
		video::EVST_VS_3_0, "shaders/blur.hlsl", "PixelShaderFunction", video::EPST_PS_3_0, bp, video::EMT_SOLID);
	shaderMaterial3 = vdriver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles("shaders/saturation.hlsl", "VertexShaderFunction",
		video::EVST_VS_3_0, "shaders/saturation.hlsl", "PixelShaderFunction", video::EPST_PS_3_0, bp, video::EMT_SOLID);
	//secondScreenQuad->setMaterialType((video::E_MATERIAL_TYPE)shaderMaterial2);
	bp->drop();

}

PostProcessEffect::~PostProcessEffect()
{

}

void PostProcessEffect::render()
{

	/*
	vdriver->setRenderTarget(renderTarget,true, true, video::SColor(0,0,0,255));
	scenemngr->drawAll();
	vdriver->setRenderTarget(secondRenderTarget, true, true, video::SColor(0,0,0,255));

	vdriver->draw2DImage(renderTarget, rect<s32>(0,0,width, height), rect<s32>(0,0,width, height));
	*/
	//first pass
	vdriver->setRenderTarget(renderTarget,true, true, video::SColor(255,0,0,255));
	screenQuad->setMaterialType((video::E_MATERIAL_TYPE)shaderMaterial1);
	//secondScreenQuad->setMaterialType((video::E_MATERIAL_TYPE)shaderMaterial2);
	//vdriver->draw2DImage(renderTarget, rect<s32>(0,0,width, height), rect<s32>(0,0,width, height));
	scenemngr->drawAll();
	vdriver->setRenderTarget(secondRenderTarget, true, true, video::SColor(255,0,0,255));
	screenQuad->setMaterialType((video::E_MATERIAL_TYPE)shaderMaterial2);
	scenemngr->drawAll();
	vdriver->setRenderTarget(video::ERT_FRAME_BUFFER, true, true);
	screenQuad->render();
	//secondScreenQuad->render();
	
}
