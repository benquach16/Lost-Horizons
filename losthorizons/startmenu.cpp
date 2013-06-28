#include "stdafx.h"
#include "startmenu.h"


StartMenu::StartMenu()
	: MenuWindow(), flip(false), config(0), confirmQuit(0)
{
	//create window
	window = guienv->addWindow(rect<s32>(0,0,iWidth,iHeight), true);
	window->setDrawBackground(false);
	window->setDraggable(false);
	window->getCloseButton()->setVisible(false);

	//setup GUI font and other stuff
	gui::IGUISkin* metallic = guienv->createSkin(gui::EGST_WINDOWS_METALLIC);
	guienv->setSkin(metallic);
	metallic->drop();
	/*gui::IGUIFont *micro = guienv->getFont("res/font/verdana_micro.xml");
	gui::IGUIFont *menu_font = guienv->getFont("res/font/large.xml");*/
	gui::IGUIFont *astro = guienv->getFont("res/font/system.xml");
	guienv->getSkin()->setFont(astro);
	
	//setup colors for gui
	for (s32 i = 0; i < gui::EGDC_COUNT; ++i) {
		SColor col = guienv->getSkin()->getColor((gui::EGUI_DEFAULT_COLOR)i);
		col.setAlpha(208);
		col.setBlue(128);
		col.setGreen(118);
		col.setRed(108);
		guienv->getSkin()->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
	}

	guienv->getSkin()->setColor(gui::EGDC_BUTTON_TEXT, SColor(255,255,255,255));
	guienv->getSkin()->setColor(gui::EGDC_HIGH_LIGHT_TEXT, SColor(255,255,255,255));
	guienv->getSkin()->setColor(gui::EGDC_3D_DARK_SHADOW, SColor(128,40,50,60));
	guienv->getSkin()->setColor(gui::EGDC_3D_SHADOW, SColor(128,80,90,100));
	guienv->getSkin()->setColor(gui::EGDC_ACTIVE_BORDER, SColor(255,145,155,165));
	guienv->getSkin()->setColor(gui::EGDC_INACTIVE_BORDER, SColor(128,80,90,100));
	guienv->getSkin()->setColor(gui::EGDC_GRAY_TEXT, SColor(128,40,50,60));
	guienv->getSkin()->setColor(gui::EGDC_WINDOW_SYMBOL, SColor(255,255,255,255));
	guienv->getSkin()->setColor(gui::EGDC_INACTIVE_CAPTION, SColor(255,200,200,200));
	guienv->getSkin()->setColor(gui::EGDC_ACTIVE_CAPTION, SColor(255,250,250,250));

	//create logo
	guienv->addImage(vdriver->getTexture("res/menu/lost_horizons_logo.png"), position2d<s32>(iWidth/2-256,0), true, window);

	//create menu buttons
	resume = guienv->addButton(rect<s32>(iWidth/2-50,iHeight/2+20,iWidth/2+50,iHeight/2+40), window, -1, L"Resume");
	newgame = guienv->addButton(rect<s32>(iWidth/2-50,iHeight/2+20,iWidth/2+50,iHeight/2+40), window, -1, L"New Game");
	loadgame = guienv->addButton(rect<s32>(iWidth/2-50,iHeight/2+60,iWidth/2+50,iHeight/2+80), window, -1, L"Load Game");
	savegame = guienv->addButton(rect<s32>(iWidth/2+10,iHeight/2+60,iWidth/2+110,iHeight/2+80), window, -1, L"Save Game");
	closegame = guienv->addButton(rect<s32>(iWidth/2-50,iHeight/2+140,iWidth/2+50,iHeight/2+160), window, -1, L"Main Menu");
	options = guienv->addButton(rect<s32>(iWidth/2-50,iHeight/2+100,iWidth/2+50,iHeight/2+120), window, -1, L"Options");
	quit = guienv->addButton(rect<s32>(iWidth/2-50,iHeight/2+140,iWidth/2+50,iHeight/2+160), window, -1, L"Quit");

	//set button visibility
	savegame->setVisible(false);

	//create child windows
	config = new OptionMenu(window);
	confirmQuit = new MessageMenu(rect<s32>(iWidth/2-120,iHeight/2-40,iWidth/2+120,iHeight/2+40), window, 0, MessageMenu::YESNO, false, false);
	confirmQuit->moveButtons(position2d<s32>(0,-5));
	confirmQuit->addText(position2d<s32>(20,15), dimension2d<u32>(60,50), L"Are you sure you want to exit?");

	//create sun for menu background
	corona = scenemngr->addBillboardSceneNode(0, dimension2d<f32>(50000,50000), vector3df(-20000,500,70000));
	corona->setMaterialTexture(0, vdriver->getTexture("res/particlewhite.bmp"));
	corona->setMaterialFlag(EMF_LIGHTING, false);
	corona->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

	scene::IBillboardSceneNode *corona2 = scenemngr->addBillboardSceneNode(corona, dimension2d<f32>(130000,110000), vector3df(0,0,0));
	corona2->setMaterialTexture(0, vdriver->getTexture("res/textures/engine_corona.png"));
	corona2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	//setup menu background
	scenemngr->setAmbientLight(SColor(64,64,64,64));	

	nebula = scenemngr->addParticleSystemSceneNode(false);
	scene::IParticleSphereEmitter *em = nebula->createSphereEmitter(vector3df(-800,0,100), 10, vector3df(0.02f,0,0), 1, 1,
																	SColor(255,200,220,225), SColor(255,200,220,225), 15000, 25000, 0,
																	dimension2d<f32>(500,500), dimension2d<f32>(2000,2000));
	nebula->setEmitter(em);
	em->drop();
	nebula->setMaterialFlag(EMF_LIGHTING, false);
	nebula->setMaterialTexture(0, vdriver->getTexture("res/textures/fog.pcx"));
	nebula->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

	scene::IParticleAffector *af = nebula->createFadeOutParticleAffector();
	nebula->addAffector(af);
	af->drop();
	
	asteroids = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh("res/models/planets/asteroid.x"));
	asteroids->setMaterialTexture(0, vdriver->getTexture("res/roid.jpg"));
	asteroids->setPosition(vector3df(-20000,0,60000));
	asteroids->setScale(vector3df(8,8,8));
}

//delete everything
StartMenu::~StartMenu()
{
	delete config;
	delete confirmQuit;
	corona->remove();
	nebula->remove();
	asteroids->remove();
}

bool StartMenu::run()
{
	if (flip != gConfig.bPlay) {
		flip = gConfig.bPlay;
		if (gConfig.bPlay) {
			newgame->setVisible(false);
			loadgame->move(position2d<s32>(-60,0));
			savegame->setVisible(true);
			quit->setVisible(false);
		} else {
			newgame->setVisible(true);
			loadgame->move(position2d<s32>(60,0));
			savegame->setVisible(false);
			quit->setVisible(true);
		}
	}
	MenuWindow::run();
	if (getVisible()) {
		if (resume->isPressed()) {
			gConfig.bPlay = true;
			return false;
		}
		if (newgame->isPressed()) {
			gConfig.bPlay = true;
			return false;
		}
		if (loadgame->isPressed()) {
			gConfig.bPlay = true;
			gConfig.bLoad = true;
			return false;
		}
		if (savegame->isPressed()) {
			gConfig.bPlay = true;
			gConfig.bSave = true;
			return false;
		}
		if (closegame->isPressed()) {
			gConfig.bPlay = false;
			return true;
		}
		if (options->isPressed()) {
			config->setVisible(true);
		}
		if (quit->isPressed()) {
			if (gConfig.bConfirmOnQuit) {
				confirmQuit->setVisible(true);
			} else {
				return false;
			}
		}
		config->run();
	}

	return !(MessageMenu::YES == confirmQuit->run());
}
