#include "stdafx.h"
#include "globals.h"
#include "dialoguetree.h"

using namespace base;
using namespace irr;
using namespace core;
using namespace scene;
using namespace gui;

DialogueTree::DialogueTree(DialogueTree *parent) : parent(parent), window(0), speaker(0),
	description(0)
{
	//how do we only show the window when shit happens?

	window = guienv->addWindow(rect<s32>(width/2-300,height/2-200,width/2+300,height/2+200), false);

}

DialogueTree::~DialogueTree()
{

}

void DialogueTree::addChild(DialogueTree *child, const std::wstring& response)
{
	//offset by num children

}
