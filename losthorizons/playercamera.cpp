#include "stdafx.h"
#include "playercamera.h"
#include "globals.h"

using namespace base;

#define DISTANCEINCREMENT 50
#define DISTANCEMINIMUM 200
#define DISTANCEMAXIMUM 1500

PlayerCamera::PlayerCamera(const core::vector3df &position)
	: cam(scenemngr->addCameraSceneNode(0, position)),
	  cameraMode(CAMERA_ORBIT),
	  distance(DISTANCEMINIMUM+DISTANCEINCREMENT),
	  angle(180), angleY(20), mouseX(0), mouseY(0)
{
	cam->setFarValue(500000);
}

PlayerCamera::~PlayerCamera()
{
	cam->remove();
}

void PlayerCamera::run(const core::vector3df &targetPos)
{
	//update camera angles and distance
	control();
	
	//change camera location
	switch (cameraMode)
	{
	case CAMERA_ORBIT:
		orbit(targetPos);
		break;
	case CAMERA_CHASE:
		//implement
		break;
	case CAMERA_TOP:
		//implement
		break;
	}
	
	//rotate camera to look at player position
	cam->setTarget(targetPos);

	//change listener position based on new player and cam positions
	sound->setListenerPosition(cam->getAbsolutePosition(), targetPos - cam->getAbsolutePosition());
}

void PlayerCamera::orbit(const vector3df &pos)
{
	//3d trig
	//this math is to determine the location of orbiting camera
	const f32 temp = cos(angleY*PI/180)*distance;
	const f32 X = sin(angle*PI/180)*temp + pos.X;
	const f32 Y = sin(angleY*PI/180)*distance + pos.Y;
	const f32 Z = cos(angle*PI/180)*temp + pos.Z; 

	//smooth out camera motion
	cam->setPosition(cam->getPosition()*0.8f + core::vector3df(X,Y,Z)*0.2f);
}

void PlayerCamera::rotateX(int x)
{
	angle += x;
	//keep it within limits
	if (angle >= 360) 
		angle -= 360;
	else if (angle < 0)
		angle += 360;
}

void PlayerCamera::rotateY(int y)
{
	angleY += y;
	//keep it within limits
	if (angleY >= 360)
		angleY -= 360;
	else if (angleY < 0)
		angleY += 360;
}

void PlayerCamera::zoom(int z)
{
	distance += z*DISTANCEINCREMENT;
	//keep it within limits
	if (distance > -DISTANCEMINIMUM && distance < 0)
		distance = DISTANCEMINIMUM;
	else if (distance >= 0 && distance < DISTANCEMINIMUM)
		distance = -DISTANCEMINIMUM;
	else if (distance < -DISTANCEMAXIMUM)
		distance = -DISTANCEMAXIMUM;
	else if (distance > DISTANCEMAXIMUM)
		distance = DISTANCEMAXIMUM;
}

void PlayerCamera::control()
{
	const int x = receiver->getMouseX();
	const int y = receiver->getMouseY();
	if (receiver->isKeyDown(KEY_RBUTTON)) {
		//we can rotate the camera around this way
		rotateX(x - mouseX);
		rotateY(y - mouseY);
	}
	mouseX = x;
	mouseY = y;
	zoom(receiver->getMouseWheel());
}
