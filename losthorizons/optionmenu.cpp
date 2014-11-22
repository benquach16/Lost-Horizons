#include "stdafx.h"
#include "optionmenu.h"
#include "globals.h"
#include "config.h"
#include <cmath>

using namespace base;

OptionMenu::OptionMenu(gui::IGUIWindow *menu)
	: MenuWindow(guienv->addWindow(rect<s32>(width/2-300,height/2-200,width/2+300,height/2+200), true, 0, menu))
{
	//create window
	window->setDraggable(false);
	window->setDrawTitlebar(false);
	window->getCloseButton()->setVisible(false);
	window->setVisible(gConfig.bFirstRun);

	close = guienv->addButton(rect<s32>(480,360,580,380), window, -1, L"Close");
	confirm = guienv->addButton(rect<s32>(360,360,460,380), window, -1, L"Apply");

	resY[1] = 576;
	resY[2] = 648;
	resY[3] = 720;
	resY[4] = 768;
	resY[5] = 900;
	resY[6] = 1080;
	resY[7] = 1440;
	resY[8] = 2160;
	
	//create resolution menu
	guienv->addStaticText(L"Resolution", rect<s32>(20,20,120,40), false ,true, window);
	resolution = guienv->addComboBox(rect<s32>(20,40,120,60), window);

	resY[0] = GetSystemMetrics(SM_CYSCREEN);
	resX[0] = GetSystemMetrics(SM_CXSCREEN);
	f32 monitorRatio = (f32)(resX[0])/resY[0];
	resolution->addItem(L"native");
	
	if (!gConfig.bFullScreen) {
		std::wstring option;
		for (unsigned i = 1; i < 9; ++i) {
			if (resY[i] < resY[0]) {
				resX[i] = (int)(floor(resY[i]*monitorRatio));
				option = std::to_wstring(resX[i]) + L" x " + std::to_wstring(resY[i]);
				resolution->addItem(option.c_str());
			}
			if (gConfig.iResolutionY == resY[i]) {
				resolution->setSelected(i);
			}
		}
	}

	//create checkboxes
	guienv->addStaticText(L"Fullscreen", rect<s32>(50,320,150,340), false, true, window);
	fullscreen = guienv->addCheckBox(gConfig.bFullScreen, rect<s32>(20,320,40,340), window);
	guienv->addStaticText(L"V-sync", rect<s32>(200,320,260,340), false, true, window);
	vsync = guienv->addCheckBox(gConfig.bVsync, rect<s32>(170,320,190,340), window);
}

OptionMenu::~OptionMenu()
{
}

void OptionMenu::run()
{
	if (close->isPressed()) {
		discard();
		window->setVisible(false);
	}
	if (confirm->isPressed()) {
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
		
		window->setVisible(false);
	}
}

void OptionMenu::discard()
{
	for (unsigned i = 0; i < 8; ++i) {
		if (gConfig.iResolutionY == resY[i]) {
			resolution->setSelected(i);
		}
	}
	fullscreen->setChecked(gConfig.bFullScreen);
	vsync->setChecked(gConfig.bVsync);
}

bool OptionMenu::get(gui::IGUICheckBox *item)
{
	return item->isChecked();
}

int OptionMenu::get(gui::IGUIComboBox *item, const int* val)
{
	return val[item->getSelected()];
}
