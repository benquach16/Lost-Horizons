#ifndef _MINIMAP_H_
#define _MINIMAP_H_

#include "ship.h"

//pretty self explanitory
//a minimap ui element
class Minimap
{
public:
	Minimap();
	~Minimap();
	void run();
	//make sure we can enlarge the minimap on the screen
	void zoomIn();
	void zoomOut();
	void enlarge();
protected:
	//we use two different run fucntions based on our bool
	void runRegular();
	void runEnlarged();
	//draw functions to make all this easier on ourselves
	//and so we have less copy paste
	void drawObject(unsigned i, const f32 x, const f32 z);
	float zoomFactor;
	bool enlarged;
};

#endif
