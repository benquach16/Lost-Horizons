#include "stdafx.h"
#include "startmenu.h"


StartMenu::StartMenu(irr::IrrlichtDevice *graphics)
	: MenuWindow(), config(0)
{
	//setup GUI font and other stuff
	graphics->getGUIEnvironment()->setSkin(graphics->getGUIEnvironment()->createSkin(gui::EGST_WINDOWS_METALLIC));
	/*gui::IGUIFont *micro = graphics->getGUIEnvironment()->getFont("res/font/verdana_micro.xml");
	gui::IGUIFont *menu_font = graphics->getGUIEnvironment()->getFont("res/font/large.xml");*/
	gui::IGUIFont *astro = graphics->getGUIEnvironment()->getFont("res/font/system.xml");
	graphics->getGUIEnvironment()->getSkin()->setFont(astro);

	//setup colors for gui
	for (s32 i = 0; i < gui::EGDC_COUNT; ++i) {
		SColor col = graphics->getGUIEnvironment()->getSkin()->getColor((gui::EGUI_DEFAULT_COLOR)i);
		col.setAlpha(208);
		col.setBlue(128);
		col.setGreen(118);
		col.setRed(108);
		graphics->getGUIEnvironment()->getSkin()->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
	}

	graphics->getGUIEnvironment()->getSkin()->setColor(gui::EGDC_BUTTON_TEXT, SColor(255,255,255,255));
	graphics->getGUIEnvironment()->getSkin()->setColor(gui::EGDC_HIGH_LIGHT_TEXT, SColor(255,255,255,255));
	graphics->getGUIEnvironment()->getSkin()->setColor(gui::EGDC_3D_DARK_SHADOW, SColor(128,40,50,60));
	graphics->getGUIEnvironment()->getSkin()->setColor(gui::EGDC_3D_SHADOW, SColor(128,80,90,100));
	graphics->getGUIEnvironment()->getSkin()->setColor(gui::EGDC_ACTIVE_BORDER, SColor(255,145,155,165));
	graphics->getGUIEnvironment()->getSkin()->setColor(gui::EGDC_INACTIVE_BORDER, SColor(128,80,90,100));
	graphics->getGUIEnvironment()->getSkin()->setColor(gui::EGDC_GRAY_TEXT, SColor(128,40,50,60));
	graphics->getGUIEnvironment()->getSkin()->setColor(gui::EGDC_WINDOW_SYMBOL, SColor(255,255,255,255));
	graphics->getGUIEnvironment()->getSkin()->setColor(gui::EGDC_INACTIVE_CAPTION, SColor(255,200,200,200));
	graphics->getGUIEnvironment()->getSkin()->setColor(gui::EGDC_ACTIVE_CAPTION, SColor(255,250,250,250));	

	//important to set up menu
	dimension2d<u32> t = graphics->getVideoDriver()->getScreenSize();

	//Create logo
	logo = graphics->getGUIEnvironment()->addImage(graphics->getVideoDriver()->getTexture("res/menu/lost_horizons_logo.png"), position2d<s32>(t.Width/2-256,0));

	//create menu buttons
	newgame = graphics->getGUIEnvironment()->addButton(rect<int>(t.Width/2-50,t.Height/2+20,t.Width/2+50,t.Height/2+40), window,0, L"New Game");
	loadgame = graphics->getGUIEnvironment()->addButton(rect<int>(t.Width/2-50,t.Height/2+60,t.Width/2+50,t.Height/2+80), window, 0, L"Load Game");
	options = graphics->getGUIEnvironment()->addButton(rect<int>(t.Width/2-50,t.Height/2+100,t.Width/2+50,t.Height/2+120), window, 0, L"Options");
	quit = graphics->getGUIEnvironment()->addButton(rect<int>(t.Width/2-50,t.Height/2+140,t.Width/2+50,t.Height/2+160), window, 0, L"Quit");

	//setup camera for menu scene
	cam = graphics->getSceneManager()->addCameraSceneNode();
	cam->setPosition(vector3df(0,0,0));
	cam->setFarValue(5000000);

	//create sun for menu background
	corona = graphics->getSceneManager()->addBillboardSceneNode(0, dimension2d<f32>(50000,50000), vector3df(-20000,500,70000));
	corona->setMaterialTexture(0, graphics->getVideoDriver()->getTexture("res/particlewhite.bmp"));
	corona->setMaterialFlag(EMF_LIGHTING, false);
	corona->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

	scene::IBillboardSceneNode *corona2 = graphics->getSceneManager()->addBillboardSceneNode(corona, dimension2d<f32>(130000,110000), vector3df(0,0,0));
	corona2->setMaterialTexture(0, graphics->getVideoDriver()->getTexture("res/textures/engine_corona.png"));
	corona2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	//setup menu background
	scene::ISceneNode *skybox = graphics->getSceneManager()->addSkyBoxSceneNode(
		graphics->getVideoDriver()->getTexture("res/textures/skyboxes/3/space_top3.jpg"),
		graphics->getVideoDriver()->getTexture("res/textures/skyboxes/3/space_bottom4.jpg"),
		graphics->getVideoDriver()->getTexture("res/textures/skyboxes/3/space_left2.jpg"),
		graphics->getVideoDriver()->getTexture("res/textures/skyboxes/3/space_right1.jpg"),
		graphics->getVideoDriver()->getTexture("res/textures/skyboxes/3/space_front5.jpg"),
		graphics->getVideoDriver()->getTexture("res/textures/skyboxes/3/space_back6.jpg"));
	graphics->getSceneManager()->setAmbientLight(SColor(64,64,64,64));	

	nebula = graphics->getSceneManager()->addParticleSystemSceneNode(false, cam);
	scene::IParticleSphereEmitter *em = nebula->createSphereEmitter(vector3df(-800,0,100), 10, vector3df(0.02f,0,0), 1, 1,
																	SColor(255,200,220,225), SColor(255,200,220,225), 15000, 25000, 0,
																	dimension2d<f32>(500,500), dimension2d<f32>(2000,2000));
	nebula->setEmitter(em);
	em->drop();
	nebula->setMaterialFlag(EMF_LIGHTING, false);
	nebula->setMaterialTexture(0, graphics->getVideoDriver()->getTexture("res/textures/fog.pcx"));
	nebula->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

	scene::IParticleAffector *af = nebula->createFadeOutParticleAffector();
	nebula->addAffector(af);
	af->drop();
	
	asteroids = graphics->getSceneManager()->addAnimatedMeshSceneNode(graphics->getSceneManager()->getMesh("res/models/planets/asteroid.x"));
	asteroids->setMaterialTexture(0, graphics->getVideoDriver()->getTexture("res/roid.jpg"));
	asteroids->setPosition(vector3df(-20000,0,60000));
	asteroids->setScale(vector3df(8,8,8));

	config = new OptionMenu(graphics);
}

//delete everything
StartMenu::~StartMenu()
{
	delete config;
	cam->remove();
	corona->remove();
	asteroids->remove();
	logo->remove();
	//resume->remove();
	newgame->remove();
	loadgame->remove();
	//savegame->remove();
	//closegame->remove();
	options->remove();
	quit->remove();
}

bool StartMenu::run()
{
	/*if (resume->isPressed()) {
		gConfig.bPlay = true;
		return false;
	}*/
	if (newgame->isPressed()) {
		gConfig.bPlay = true;
		return false;
	}
	if (loadgame->isPressed()) {
		gConfig.bPlay = true;
		gConfig.bLoad = true;
		return false;
	}
	/*if (savegame->isPressed()) {
		gConfig.bPlay = true;
		gConfig.bSave = true;
		return false;
	}*/
	/*if (closegame->isPressed()) {
		gConfig.bPlay = false;
		return true;
	}*/
	if (options->isPressed()) {
		config->setVisible(true);
	}
	if (quit->isPressed()) {
		quit->setPressed(false);
		gConfig.bPlay = false;
		return false;
	}
	config->run();

	return true;
}
