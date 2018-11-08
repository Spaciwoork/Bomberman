/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** Created by MP,
*/

#ifndef FIRE_HPP
# define FIRE_HPP

#include "IObject.hpp"
#include <iostream>
#include <irrlicht/irrlicht.h>

class Fire
{
	public:
	Fire(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
		irr::scene::ITriangleSelector **selector);
	~Fire();
	void setPosition(irr::core::vector3df pos);
	void FireDrop();

	protected:
	irr::scene::IParticleSystemSceneNode* _Particle;
};

#endif /* !CPP_FIRE_HPP */
