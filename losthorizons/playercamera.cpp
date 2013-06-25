#include "playercamera.h"

PlayerCamera::PlayerCamera(irr::IrrlichtDevice *graphics, const vector3df &position) : cameraMode(E_CAMERA_ORBIT),
	angle(0), angleY(0), distance(200)
{
	cam = graphics->getSceneManager()->addCameraSceneNode(0, position);
}

void PlayerCamera::run(const vector3df &pos, float frameDeltaTime)
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
	if(angleY<0)
		angleY+=360;

	if(cameraMode == E_CAMERA_ORBIT)
	{
		orbit(pos, frameDeltaTime);
	}
}

void PlayerCamera::orbit(const vector3df &pos, float frameDeltaTime)
{

	core::vector3df playerCameraPos;

	//3d trig
	//this math is to determine the location of orbiting camera
	playerCameraPos.Y = sin(angleY*3.14/180)*distance;
	playerCameraPos.Y += pos.Y;

	float temp;
	temp=cos(angleY*3.14/180);


	//some code to calculate position
	core::vector3df old;
	playerCameraPos.X = (sin((angle) * 3.141 / 180) * (distance));
	playerCameraPos.X = playerCameraPos.X*temp;
	playerCameraPos.X  += pos.X;

	playerCameraPos.Z  = (cos((angle) * 3.141/ 180) * (distance)); 
	playerCameraPos.Z = playerCameraPos.Z*temp;
	playerCameraPos.Z += pos.Z;


	//smooth out camera motion
	old = cam->getPosition();
	old=old*0.8+playerCameraPos*0.2f;
	cam->setPosition(old);
}

void PlayerCamera::rotateX(int x)
{
	int i=x-this->x;
	this->x=x;
	angle+=i;
}

void PlayerCamera::rotateY(int y)
{
	int i=y-this->y;
	this->y = y;
	angleY+=i;
}
