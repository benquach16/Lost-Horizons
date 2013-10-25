#include "stdafx.h"
#include "playercamera.h"
#include "globals.h"

using namespace base;

PlayerCamera::PlayerCamera(const core::vector3df &position)
	: cam(scenemngr->addCameraSceneNode(0, position)), cameraMode(CAMERA_ORBIT), distance(200), angle(0), angleY(0),
	  mouseX(0), mouseY(0), oldMouseWheel(0)
{
	cam->setFarValue(500000);
}

PlayerCamera::~PlayerCamera()
{
	cam->remove();
}

void PlayerCamera::run(const core::vector3df &pos, f32 frameDeltaTime)
{
	//constantly look at player position
	//and rotate around it
	cam->setTarget(pos);
	//if angle is too big or too small
	//put it back in 360 limit
	if (angle > 360) 
		angle -= 360;

	else if (angle < 0)
		angle += 360;

	if (angleY>360)
		angle-=360;

	else if (angleY<0)
		angleY+=360;

	sound->setListenerPosition(cam->getAbsolutePosition(), (cam->getTarget() - cam->getAbsolutePosition()));
	if (cameraMode == CAMERA_ORBIT)
		orbit(pos, frameDeltaTime);
}

void PlayerCamera::orbit(const vector3df &pos, f32 frameDeltaTime)
{
	core::vector3df playerCameraPos;

	//3d trig
	//this math is to determine the location of orbiting camera
	playerCameraPos.Y = (f32)sin(angleY*3.14/180)*distance + pos.Y;

	f32 temp = (f32)cos(angleY*3.14/180);

	//some code to calculate position
	playerCameraPos.X = (f32)(sin((angle)*3.141/180)*(distance)*temp + pos.X);
	playerCameraPos.Z = (f32)(cos((angle)*3.141/180)*(distance)*temp + pos.Z); 

	//smooth out camera motion
	cam->setPosition(cam->getPosition()*0.8f + playerCameraPos*0.2f);
}

void PlayerCamera::rotateX(int x)
{
	int i = x - mouseX;
	mouseX = x;
	angle += i;
}

void PlayerCamera::rotateY(int y)
{
	int i = y - mouseY;
	mouseY = y;
	angleY += i;
}

void PlayerCamera::zoom(int z)
{
	if(z != oldMouseWheel)
	{
		distance -= (z - oldMouseWheel)*50;
		oldMouseWheel = z;
	}
}

void PlayerCamera::updateMousePosition(int x, int y)
{
	mouseX = x;
	mouseY = y;
}
