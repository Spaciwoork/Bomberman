//
// EPITECH PROJECT, 2018
// Crate
// File description:
// Crate
//

#ifndef CRATE_HPP
# define CRATE_HPP

#include <iostream>
#include <irrlicht/irrlicht.h>
#include "Tools.hpp"
#include "IObject.hpp"

class Crate : public IObject
{
public:
	Crate(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
	      irr::scene::ITriangleSelector **selector, std::string path_obj);
	virtual ~Crate();
	virtual void DropObject();

private:
};

#endif
