//
// EPITECH PROJECT, 2018
// Crate
// File description:
// Crate
//

#ifndef WALL_HPP
# define WALL_HPP

#include <iostream>
#include <irrlicht/irrlicht.h>
#include "Tools.hpp"
#include "IObject.hpp"

class Wall : public IObject
{
public:
	Wall(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
	     irr::scene::ITriangleSelector **selector, std::string path_obj);
	virtual ~Wall();
private:
};

#endif
