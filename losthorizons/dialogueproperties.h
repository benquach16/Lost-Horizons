#ifndef _DIALOGUEPROPERTIES_H_
#define _DIALOGUEPROPERTIES_H_

#include "dialoguetree.h"
#include <string>

class DialogueProperties
{
public:
	DialogueProperties(const std::string& f);
	~DialogueProperties();
	//need this for recursive development
	DialogueTree* createDialogueTree(irr::io::IXMLReader *file);
protected:
	DialogueTree *tree;
};

#endif
