#include "stdafx.h"
#include "rearmmenu.h"
#include "globals.h"
#pragma hdrstop

using namespace base;

RearmMenu::RearmMenu()
{
	//make important stuff
	//do render to texture
	window = guienv->addWindow(rect<s32>(20,20,800,800), false, L"Rearm");
	shipsInFleet = guienv->addListBox(rect<s32>(40,40,100,600),window);

	//render to texture 
	rt = vdriver->addRenderTargetTexture(core::dimension2d<u32>(512,512), "ShipRTT");
	shipCamera = scenemngr->addCameraSceneNode(0,vector3df(100,0,0),vector3df(0,0,0),-1,false);

	
	//set the texture to a something	
	

}

RearmMenu::~RearmMenu()
{
	
}

void RearmMenu::loadFleet(const Fleet* fleet)
{
	//load the ships
	for(unsigned i = 0; i < fleet->size(); i++)
	{
		shipsInFleet->addItem(L"1");
	}
}

void RearmMenu::run()
{


	//this is gunna be a right bitch
	//temporarily swap the cameras
	//THIS MUST BE RUN BEFORE POSTPROCESSING CALLS
	if(rt)
	{
		//how do we run this before the render calls?
		
		ICameraSceneNode *cam = scenemngr->getActiveCamera();
		vdriver->setRenderTarget(rt, true, true, video::SColor(0,0,0,255));


		scenemngr->setActiveCamera(shipCamera);

		//draaw what we want to draw here
		
		// set back old render target
		// The buffer might have been distorted, so clear it

		vdriver->setRenderTarget(0, true, true, 0);
		//could we draw the render here?

		vdriver->draw2DImage(rt, rect<s32>(40,40,600,600), rect<s32>(0,0,512,512));
		scenemngr->setActiveCamera(cam);
	}
}

