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
	void setParent(DialogueTree *parent);
	void setSpeaker(const std::wstring& speaker);
	void setDescription(const std::wstring& description);
	void setSpeakerImage(const std::wstring& filepath);

	void clear();
	
protected:
	std::wstring speaker;
	std::wstring description;
	irr::gui::IGUIImage *speakerImage;

	DialogueTree *parent;
	//this is undoubtedly, going to be awful
	std::vector<std::pair<irr::gui::IGUIButton*, DialogueTree*> > children;
};


#endif