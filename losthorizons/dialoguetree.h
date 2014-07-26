#ifndef _DIALOGUETREE_H_
#define _DIALOGUETREE_H_

#include <vector>
#include <string>
#include <irrlicht.h>

//so we can implement a basic dialog system for mission intros/tutorials/etc
class DialogueTree
{
public:
	DialogueTree(DialogueTree *parent = 0);
	~DialogueTree();
	void addChild(DialogueTree *child);

protected:
	std::string speaker;
	std::string description;
	irr::gui::IGUIImage *speakerImage;

	DialogueTree *parent;
	std::vector<DialogueTree*> children;
};


#endif