#include "stdafx.h"
#include "playercamera.h"

PlayerCamera::PlayerCamera(irr::IrrlichtDevice *graphics, const vector3df &position) : cameraMode(CAMERA_ORBIT),
	angle(0), angleY(0), distance(200), mouseX(0), mouseY(0), oldMouseWheel(0)
{
	cam = graphics->getSceneManager()->addCameraSceneNode(0, position);
	cam->setFarValue(500000);
}

PlayerCamera::~PlayerCamera()
{
	cam->remove();
}

void PlayerCamera::run(const vector3df &pos, f32 frameDeltaTime)
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

	if(angleY>360)
		angle-=360;
	else if(angleY<0)
		angleY+=360;
	soundmngr->setListenerPosition(cam->getAbsolutePosition(), (cam->getTarget() - cam->getAbsolutePosition()));
	if(cameraMode == CAMERA_ORBIT)
	{
		orbit(pos, frameDeltaTime);
	}
}

void PlayerCamera::orbit(const vector3df &pos, f32 frameDeltaTime)
{

	core::vector3df playerCameraPos;

	//3d trig
	//this math is to determine the location of orbiting camera
	playerCameraPos.Y = (f32)sin(angleY*3.14/180)*distance;
	playerCameraPos.Y += pos.Y;

	f32 temp;
	temp = (f32)cos(angleY*3.14/180);


	//some code to calculate position
	core::vector3df old;
	playerCameraPos.X = (f32)(sin((angle) * 3.141 / 180) * (distance));
	playerCameraPos.X = playerCameraPos.X*temp;
	playerCameraPos.X += pos.X;

	playerCameraPos.Z = (f32)(cos((angle) * 3.141/ 180) * (distance)); 
	playerCameraPos.Z = playerCameraPos.Z*temp;
	playerCameraPos.Z += pos.Z;


	//smooth out camera motion
	old = cam->getPosition();
	old = old*0.8f+playerCameraPos*0.2f;
	cam->setPosition(old);
}

void PlayerCamera::rotateX(int x)
{
	int i=x-mouseX;
	mouseX=x;
	angle+=i;
}

void PlayerCamera::rotateY(int y)
{
	int i=y-mouseY;
	mouseY = y;
	angleY+=i;
}

void PlayerCamera::zoom(int z)
{
	if(z != oldMouseWheel)
	{
		distance -= (z - oldMouseWheel) * 50;
		oldMouseWheel = z;
	}

}

void PlayerCamera::updateMousePosition(int x, int y)
{
	mouseX = x;
	mouseY = y;
}
