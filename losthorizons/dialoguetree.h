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
	void addChild(DialogueTree *child, const std::wstring &response);
	void setParent(DialogueTree *parent);
	void setSpeaker(const std::wstring& speaker);
	void setDescription(const std::wstring& description);
	void setSpeakerImage(const std::wstring& filepath);

	void clear();
	
protected:
	irr::gui::IGUIImage *speakerImage;
	irr::gui::IGUIStaticText *speaker;
	irr::gui::IGUIStaticText *description;
	irr::gui::IGUIWindow *window;

	DialogueTree *parent;
	//this is undoubtedly, going to be awful
	std::vector<std::pair<irr::gui::IGUIButton*, DialogueTree*> > children;
};


#endif