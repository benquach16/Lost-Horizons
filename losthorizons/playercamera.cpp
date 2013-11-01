#include "stdafx.h"
#include "playercamera.h"
#include "globals.h"

using namespace base;

PlayerCamera::PlayerCamera(const core::vector3df &position)
	: cam(scenemngr->addCameraSceneNode(0, position)), cameraMode(CAMERA_ORBIT), distance(200), angle(180), angleY(20),
	  mouseX(0), mouseY(0), oldMouseWheel(0)
{
	cam->setFarValue(500000);
}

PlayerCamera::~PlayerCamera()
{
	cam->remove();
}

void PlayerCamera::run(const core::vector3df &pos)
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

	if (angleY > 360)
		angle -= 360;
	else if (angleY < 0)
		angleY += 360;

	sound->setListenerPosition(cam->getAbsolutePosition(), (cam->getTarget() - cam->getAbsolutePosition()));
	if (cameraMode == CAMERA_ORBIT)
		orbit(pos);
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
	angle -= mouseX - x;
	mouseX = x;
}

void PlayerCamera::rotateY(int y)
{
	angleY -= mouseY - y;
	mouseY = y;
}

void PlayerCamera::zoom(int z)
{
	if (z != oldMouseWheel) {
		distance += (oldMouseWheel - z)*50;
		if (distance > -150 && distance < 150) {
			distance *= -1;
			while (distance > -150 && distance < 150)
				distance += distance < 0 ? -50 : 50;
		}
		else if (distance < -1500)
			distance = -1500;
		else if (distance > 1500)
			distance = 1500;
		oldMouseWheel = z;
	}
}

void PlayerCamera::updateMousePosition(int x, int y)
{
	mouseX = x;
	mouseY = y;
}
