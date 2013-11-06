#include "stdafx.h"
#include "storetab.h"
#include "globals.h"

using namespace base;

StoreTab::StoreTab(IGUITabControl *tabs, Inventory &playerData)
	: MenuTab(tabs->addTab(L"Store")), playerData(playerData)
{
	//initialize this
	playerInventory = guienv->addListBox(rect<s32>(20,40, 380, 300), tab);
	stationInventory = guienv->addListBox(rect<s32>(420, 40, 780, 300), tab);
	guienv->addStaticText(L"Your Cargo", rect<s32>(20,20,380,40), false, true, tab);
	guienv->addStaticText(L"For Sale", rect<s32>(420, 20, 780, 40), false, true, tab);
	selectedValue = guienv->addStaticText(L"Value :", rect<s32>(400, 320, 600, 340), false, true, tab);
	selectedWeight = guienv->addStaticText(L"Weight :", rect<s32>(620, 320, 780, 340), false, true, tab);
	selectedDescription = guienv->addStaticText(L"", rect<s32>(20, 360, 780, 400), false, true, tab);
	sellButton = guienv->addButton(rect<s32>(20,420,120,440), tab, -1, L"Sell");
	buyButton = guienv->addButton(rect<s32>(680, 420, 780, 440), tab, -1, L"Buy");
	playerCash = guienv->addStaticText(L"Your Credits :", rect<s32>(140, 420, 440, 440), false, true, tab);
}

StoreTab::~StoreTab()
{
}

void StoreTab::run(Inventory &stationData)
{
	//run through the store tab
	//uis tend to have a ton of bloated code
	loadInventories(playerData.getConvertedInventory(), stationData.getConvertedInventory());

	playerCash->setText((stringw(L"Your Credits :") + stringw(playerData.getCredits())).c_str());
	int index = playerInventory->getSelected();

	//this is needed to maintain syncing between the index and objectmanager enum
	std::vector<ObjectManager::E_ITEM_LIST> syncedInventory = playerData.getConvertedInventoryNoSpaces();
	if (index != -1) {
		//has something selected so we load its information
		selectedValue->setText((stringw(L"Value :") + stringw(ObjectManager::itemList[syncedInventory[index]]->getPrice())).c_str());
		selectedWeight->setText((stringw(L"Weight :") + stringw(ObjectManager::itemList[syncedInventory[index]]->getWeight())).c_str());
		selectedDescription->setText(ObjectManager::itemList[syncedInventory[index]]->getDesc());

		if (sellButton->isPressed()) {
			//sell selected item
			playerData.addCredits(ObjectManager::itemList[syncedInventory[index]]->getPrice());
			playerData.removeItem(syncedInventory[index]);
			stationData.addItem(syncedInventory[index], 1);
			playerInventory->clear();
			stationInventory->clear();
		}
	} else {
		//reset text if nothing is selected
		selectedValue->setText(L"Value :");
		selectedWeight->setText(L"Weight :");
		selectedDescription->setText(L"");
	}
	index = stationInventory->getSelected();
	syncedInventory = stationData.getConvertedInventoryNoSpaces();
	if (index != -1) {
		//has something selected so we load its information
		selectedValue->setText((stringw(L"Value :") + stringw(ObjectManager::itemList[syncedInventory[index]]->getPrice())).c_str());
		selectedWeight->setText((stringw(L"Weight :") + stringw(ObjectManager::itemList[syncedInventory[index]]->getWeight())).c_str());
		selectedDescription->setText(ObjectManager::itemList[syncedInventory[index]]->getDesc());
		if (buyButton->isPressed()) {
			//sell selected item
			playerData.addCredits(-ObjectManager::itemList[syncedInventory[index]]->getPrice());
			playerData.addItem(syncedInventory[index], 1);
			stationData.removeItem(syncedInventory[index]);
			playerInventory->clear();
			stationInventory->clear();
		}
	}
}

//protected function
void StoreTab::loadInventories(std::vector<std::wstring> playerConverted, std::vector<std::wstring> stationConverted)
{
	//updating is slow!
	//only update when something is for sure changed!
	if (!playerInventory->getItemCount()) {
		for (unsigned i = 0; i < playerConverted.size(); ++i) {
			playerInventory->addItem(playerConverted[i].c_str());
		}
	}

	if (!stationInventory->getItemCount()) {
		for (unsigned i = 0; i < stationConverted.size(); ++i) {
			stationInventory->addItem(stationConverted[i].c_str());
		}		
	}
}
