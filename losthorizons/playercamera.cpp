#include "playercamera.h"

PlayerCamera::PlayerCamera(irr::IrrlichtDevice *graphics, const vector3df &position, const vector3df &rotation)
{
	cam = graphics->getSceneManager()->addCameraSceneNode(0, position, rotation);

}

void PlayerCamera::run(const vector3df &pos)
{
	//constantly look at player position
	//and rotate around it
	cam->setTarget(pos);
}
