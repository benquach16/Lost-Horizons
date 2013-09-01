#include "stdafx.h"
#include "intercom.h"

Intercom::Intercom(Player *player) : player(player), listBox(0), tabs(0)
{
	listBox = guienv->addListBox(rect<s32>(iWidth-300, iHeight-180, iWidth, iHeight));
	listBox->setAutoScrollEnabled(true);
	listBox->addItem(L"Test Message");
	listBox->addItem(L"Test Message");
	listBox->addItem(L"Test Message");
	listBox->addItem(L"Test Message");
	listBox->addItem(L"Test Message");
	listBox->addItem(L"Test Message");
	listBox->addItem(L"Longer Test Message so we can Test how length affects the comms");
	listBox->addItem(L"Test Message");
	listBox->addItem(L"Test Message");
	listBox->addItem(L"Test Message");
	listBox->addItem(L"Test Message");
	listBox->addItem(L"Test Message");
	listBox->addItem(L"Test Message2");
}

Intercom::~Intercom()
{
	listBox->remove();
}

void Intercom::run()
{
	//make sure we delete old messages
	if(listBox->getItemCount() > 8)
	{
		listBox->removeItem(0);
	}
	if(player->getInfo().shield < 10)
	{
	}
}
