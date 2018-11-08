/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by MP,
*/

#include "Camera.hpp"

Camera::Camera (irr::scene::ISceneManager *sceneManager,
		irr::core::vector3df cam_pos, bool type)
{
	std::cout << "booleen : " << type << std::endl;
	if (type == false)
	{
		_Cam = sceneManager->addCameraSceneNode();
		_Cam->setPosition(irr::core::vector3df(2, cam_pos.Y - 3,
						       cam_pos.Y / 2));
		_Cam->setTarget(irr::core::vector3df(cam_pos.X / 2 - 2, 0,
						     cam_pos.Y/ 2));
	}
	else {
		_Cam = sceneManager->addCameraSceneNodeFPS();
		_Cam->setPosition(irr::core::vector3df(cam_pos.X,
						       cam_pos.Y + 1.5,
						       cam_pos.Z - 1));
	}
}

Camera::~Camera ()
{
}

void Camera::SetCamPosition (irr::core::vector3df tag, irr::core::vector3df axe,
			     irr::core::vector3df rot)
{
	_Cam->setPosition(irr::core::vector3df(axe.X, axe.Y + 1.5, axe.Z));
	_Cam->setRotation(rot);
	_Cam->setTarget(tag);
	(void)tag;
	(void)rot;
	(void)axe;
}
