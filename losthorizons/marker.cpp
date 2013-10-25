#include "stdafx.h"
#include "marker.h"

Marker::Marker() : Object(L"res/models/nav_buoy.X")
{
	setScale(vector3df(0.5,0.5,0.5));
}

void Marker::run(f32 frameDeltaTime)
{
	vector3df rot = getRotation();
	rot.Y += 10 * frameDeltaTime;
	setRotation(rot);
	Object::run(frameDeltaTime);
}
