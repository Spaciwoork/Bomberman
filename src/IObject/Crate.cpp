//
// EPITECH PROJECT, 2018
// Crate
// File description:
// Crate
//

#include "Crate.hpp"

Crate::Crate(irr::video::IVideoDriver *driver,
	     irr::scene::ISceneManager *sceneManager,
	     irr::scene::ITriangleSelector **selector, std::string path_obj)
	:IObject(true, false)
{
	if (driver == nullptr || sceneManager == nullptr)
		return ;
	_mesh = sceneManager->addAnimatedMeshSceneNode(
                sceneManager->getMesh(path_obj.c_str()), 0,
		isDESTRUCTIBLEandPASSE);
	_path_obj = path_obj;
        _mesh->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
        _mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_mesh->setRotation(irr::core::vector3df(
		0, Tools::getNbrRandom(0, 4) * 90, 0));
	*selector = sceneManager->createTriangleSelector(
		(irr::scene::IAnimatedMeshSceneNode*)_mesh);
	_mesh->setTriangleSelector(*selector);
	_type = Type::T_CRATE;
}

Crate::~Crate()
{
}

void Crate::DropObject()
{
	_mesh->drop();
}
