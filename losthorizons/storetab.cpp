#include "stdafx.h"
#include "storetab.h"

StoreTab::StoreTab(gui::IGUITabControl *tabs) : MenuTab()
{
	tab = tabs->addTab(L"Store");
}

StoreTab::~StoreTab()
{
}

void StoreTab::run()
{
}
