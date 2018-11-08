//
// EPITECH PROJECT, 2018
// Crate
// File description:
// Crate
//

#include "Wall.hpp"

Wall::Wall(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
	   irr::scene::ITriangleSelector **selector, std::string path_obj)
	:IObject(false, false)
{
	if (driver == nullptr || sceneManager == nullptr)
		return ;
	_mesh = sceneManager->addAnimatedMeshSceneNode(
		sceneManager->getMesh(path_obj.c_str()), 0,
		isINDESTRUCTIBLE);
	_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_path_obj = path_obj;
}

Wall::~Wall()
{
}