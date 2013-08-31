#ifndef _CARGO_H_
#define _CARGO_H_

#include "targetableobject.h"
#include "inventory.h"


//cargo container class for loot
class Cargo : public TargetableObject
{
public:
	//we need this just so we can delete them later 
	static std::vector<Cargo*> allCargo;
	//constructors
	//if randomzeContents is false, make an empty container
	Cargo(const vector3df &position, bool randomizeContents);
	Cargo(const vector3df &position, const Inventory &inv);
	virtual ~Cargo();
	virtual void run(f32 frameDeltaTime);

	//some important accessors
	const virtual E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const;
	Inventory& getInventory();
	const Inventory& getInventory() const;
protected: 
	//store stuff thats in the cargo
	Inventory inventory;
};

#endif
