/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by MP,
*/

#ifndef DEATH_GHOSTS_HPP
# define DEATH_GHOSTS_HPP

#include <iostream>
#include <time.h>
#include <chrono>
#include <irrlicht/irrlicht.h>


class Death_Ghosts
{
	public:
	Death_Ghosts(irr::video::IVideoDriver *driver,
	      irr::scene::ISceneManager *sceneManager,
	      irr::core::vector3df pos);
	~Death_Ghosts();
	irr::scene::IAnimatedMeshSceneNode *getMesh();
	void run_out();

	protected:
	irr::scene::IAnimatedMeshSceneNode *_Mesh;
};

#endif /* !DEATH_GHOSTS_HPP */