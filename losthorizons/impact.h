#ifndef _IMPACT_H_
#define _IMPACT_H_

#include "effect.h"

//part of the sfx classes
//small impact effect that is caused from projectiles

class Impact : public Effect
{
public:
	Impact();
	~Impact();
	virtual void run();
};

#endif
