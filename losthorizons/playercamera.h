#ifndef _PLAYERCAMERA_H_
#define _PLAYERCAMERA_H_

//mostly an orbiting camera
//but can also be a top down camera

#include "irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;

class PlayerCamera
{
public:

	enum E_CAMERA_MODES
	{
		E_CAMERA_ORBIT = 0,
		E_CAMERA_CHASE = 1,
		E_CAMERA_TOP = 2
	};

	PlayerCamera(irr::IrrlichtDevice *graphics, const vector3df &position = vector3df(0,0,0));
	~PlayerCamera();
	void run(const vector3df &pos, float frameDeltaTime);
	void orbit(const vector3df &pos, float frameDeltaTime);
	void rotateX(int x);
	void rotateY(int y);
	void zoom(int z);
private:
	scene::ICameraSceneNode *cam; 
	float distance;		//distance from camera to player
	E_CAMERA_MODES cameraMode;

	//we need two angles cause there are two circles
	float angle, angleY;

	int x, y;
	int oldMouseWheel;
};

#endif
