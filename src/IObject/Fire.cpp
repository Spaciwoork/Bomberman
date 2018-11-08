/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** Created by MP,
*/

#include "Fire.hpp"
#include "Tools.hpp"

Fire::Fire(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
	   irr::scene::ITriangleSelector **selector)
{
	_Particle = sceneManager->addParticleSystemSceneNode(false);

	irr::scene::IParticleEmitter* em = _Particle->createBoxEmitter(
		irr::core::aabbox3d<irr::f32>(0,0,0,0,0,0),
		irr::core::vector3df(0.0001f,0.0004f,0.0001f),
		80,100,
		irr::video::SColor(0,255,255,255),
		irr::video::SColor(0,255,255,255),
		800,2000,0,
		irr::core::dimension2df(0.1f,0.1f),
		irr::core::dimension2df(2.f,2.f));
	_Particle->setEmitter(em);
	em->drop();
	irr::scene::IParticleAffector* paf = _Particle->
		createFadeOutParticleAffector();
	_Particle->addAffector(paf);
	paf->drop();
	_Particle->setScale(irr::core::vector3df(0.002, 0.002, 0.001));
	_Particle->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_Particle->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	_Particle->setMaterialTexture(0, driver->getTexture(
		FILEPATH "media/fire/fireball.bmp"));
	_Particle->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	_Particle->setID(5);
	(void)selector;
	(void)driver;
}

Fire::~Fire()
{
}

void Fire::setPosition(irr::core::vector3df pos)
{
	_Particle->setPosition(pos);
}

void Fire::FireDrop()
{
	_Particle->drop();
}
