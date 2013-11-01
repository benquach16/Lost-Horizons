#include "stdafx.h"
#include "marker.h"
#include "globals.h"

using namespace base;

#define SPINSPEED 10

Marker::Marker()
	: Object(L"res/models/nav_buoy.X")
{
	setScale(vector3df(0.5,0.5,0.5));
}

bool Marker::run()
{
	vector3df rot = getRotation();
	rot.Y += SPINSPEED*frameDeltaTime;
	setRotation(rot);
	return Object::run();
}
