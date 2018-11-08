/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by MP,
*/

#ifndef CAMERA_HPP
# define CAMERA_HPP

#include <iostream>
#include <irrlicht/irrlicht.h>

class Camera
{
	public:
	Camera(irr::scene::ISceneManager *sceneManager,
	       irr::core::vector3df cam_pos, bool type);
	~Camera ();
	void SetCamPosition(irr::core::vector3df per, irr::core::vector3df axe,
			    irr::core::vector3df rot);
	protected:
	irr::scene::ICameraSceneNode* _Cam;
};

#endif /* !CAMERA_HPP */
