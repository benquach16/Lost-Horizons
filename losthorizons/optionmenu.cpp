#include "stdafx.h"
#include "optionmenu.h"
#include <string>
#include <cmath>
#include <iostream>

//setup GUI and initialize variables
OptionMenu::OptionMenu(irr::IrrlichtDevice *graphics)
	: MenuWindow()
{
	dimension2d<u32> t;
	t = graphics->getVideoDriver()->getScreenSize();
	//create window
	window = graphics->getGUIEnvironment()->addWindow(rect<s32>(t.Width/2-300, t.Height/2-200, t.Width/2+300, t.Height/2+200), true, L"Options");
	window->setDraggable(false);
	window->setDrawTitlebar(false);
	window->getCloseButton()->setVisible(false);

	quit = graphics->getGUIEnvironment()->addButton(rect<s32>(480,360,580,380), window,-1, L"Close");
	apply = graphics->getGUIEnvironment()->addButton(rect<s32>(360,360,460,380), window,-1, L"Apply");

	resY[1] = 576;
	resY[2] = 648;
	resY[3] = 720;
	resY[4] = 768;
	resY[5] = 900;
	resY[6] = 1080;
	resY[7] = 1440;
	resY[8] = 2160;

	//create resolution menu
	graphics->getGUIEnvironment()->addStaticText(L"Resolution", rect<s32>(20,20,120,40), false ,true, window);
	resolution = graphics->getGUIEnvironment()->addComboBox(rect<s32>(20,40,120,60), window);

	resY[0] = GetSystemMetrics(SM_CYSCREEN);
	resX[0] = GetSystemMetrics(SM_CXSCREEN);
	double monitorRatio = static_cast<double>(resX[0]) / resY[0];
	resolution->addItem(L"native");

	if (!gConfig.bFullScreen) {
		std::string temp(" x ");
		std::wstring x(temp.begin(), temp.end());
		std::wstring option;
		for (unsigned i = 1; i < 9; ++i) {
			if (resY[i] < resY[0]) {
				resX[i] = static_cast<int>(floor(resY[i] * monitorRatio));
				option = std::to_wstring(resX[i]) + x + std::to_wstring(resY[i]);
				resolution->addItem(option.c_str());
			}
			if (gConfig.iResolutionY == resY[i]) {
				resolution->setSelected(i);
			}
		}
	}

	graphics->getGUIEnvironment()->addStaticText(L"Fullscreen", rect<s32>(50,320,150,340), false, true, window);
	fullscreen = graphics->getGUIEnvironment()->addCheckBox(gConfig.bFullScreen, rect<s32>(20,320,40,340), window);
	graphics->getGUIEnvironment()->addStaticText(L"V-sync", rect<s32>(200,320,260,340), false, true, window);
	vsync = graphics->getGUIEnvironment()->addCheckBox(gConfig.bVsync, rect<s32>(170,320,190,340), window);

	setVisible(gConfig.bFirstRun);
}

OptionMenu::~OptionMenu()
{
}

void OptionMenu::restart()
{
	for (unsigned i = 0; i < 8; ++i) {
		if (gConfig.iResolutionY == resY[i]) {
			resolution->setSelected(i);
		}
	}
	fullscreen->setChecked(gConfig.bFullScreen);
	vsync->setChecked(gConfig.bVsync);
}

void OptionMenu::run()
{
	//ensure menu is hidden or not hidden
	MenuWindow::run();
	if (quit->isPressed()) {
		restart();
		setVisible(false);
	}
	if (apply->isPressed()) {
		if (!gConfig.bFullScreen && gConfig.iResolutionX != get(resolution, resX)) {
			gConfig.iResolutionX = get(resolution, resX);
			gConfig.iResolutionY = get(resolution, resY);
			gConfig.bRestart = true;
		}
		if (gConfig.bFullScreen != get(fullscreen)) {
			gConfig.bFullScreen = get(fullscreen);
			gConfig.bRestart = true;
		}
		if (gConfig.bVsync != get(vsync)) {
			gConfig.bVsync = get(vsync);
			gConfig.bRestart = true;
		}
		
		setVisible(false);
	}
}

bool OptionMenu::get(gui::IGUICheckBox *item)
{
	return item->isChecked();
}

int OptionMenu::get(gui::IGUIComboBox *item, const int* val)
{
	return val[item->getSelected()];
}
