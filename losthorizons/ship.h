#ifndef _SHIP_H_
#define _SHIP_H_

#include <list>

#include "targetableobject.h"

//contain the list inside ship class so all ships can access any other ship if needed
static std::list<CShip*> all_ships;

class CShip : public CTargetableObject
{
public:
	CShip();
	//copy constructor
	CShip(const CShip &s);
	//overloaded assignment operator
	CShip& operator=(const CShip &s);
	~CShip();
private:
	//iterator to 'this'
	std::list<CShip*>::iterator it;
};

#endif