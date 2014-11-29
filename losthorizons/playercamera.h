#ifndef _PLAYERCAMERA_H_
#define _PLAYERCAMERA_H_

//mostly an orbiting camera
//but can also be a top down camera

#include "stdafx.h"

using namespace irr;

class PlayerCamera
{
public:
	enum E_CAMERA_MODE
	{
		CAMERA_ORBIT,
		CAMERA_CHASE,
		CAMERA_TOP
	};

	PlayerCamera(const core::vector3df &position = core::vector3df(0.f,0.f,0.f));
	~PlayerCamera();
	void run(const core::vector3df &targetPos);
	void orbit(const core::vector3df &pos);
	void rotateX(int x);
	void rotateY(int y);
	void zoom(int z);
	
private:
	void control();

	scene::ICameraSceneNode *cam; 
	E_CAMERA_MODE cameraMode;
	//distance from camera to player
	f32 distance;

	//we need two angles cause there are two circles
	f32 angle, angleY;

	int mouseX, mouseY;
};

#endif
