/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by MP,
*/

#include "Tools.hpp"
#include "Light.hpp"

Light::Light (irr::scene::ISceneManager *sceneManager,
	      irr::video::IVideoDriver *driver)
{
	_sceneManager = sceneManager;
	_driver = driver;
}

Light::~Light ()
{
}

void Light::createLightDivine (irr::scene::ISceneNode *mesh)
{
	_DivineLight = _sceneManager->addLightSceneNode(
		mesh,
		irr::core::vector3df(0, 0,  0),
		irr::video::SColorf(
			0.5f, 1.0f, 0.5f, 0.0f), 10.f);
	irr::scene::ISceneNodeAnimator* animDivine =
		_sceneManager->createFlyCircleAnimator(
			mesh->getPosition(), 25.0f, 0.0001f,
			irr::core::vector3df(1.f, 0.9f, 0.f));
	_DivineLight->addAnimator(animDivine);
	animDivine->drop();
	irr::scene::IBillboardSceneNode* bill =
		_sceneManager->addBillboardSceneNode(
		_DivineLight, irr::core::dimension2d<irr::f32>(10, 10));
	bill->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	bill->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	bill->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	bill->setMaterialTexture(0, _driver->getTexture(
		FILEPATH "media/fire/particlewhite.bmp"));
}

void Light::createDivine (irr::scene::ISceneNode *mesh)
{
	createLightDivine(mesh);
	_Divine = _sceneManager->addParticleSystemSceneNode(false, _DivineLight);
	irr::scene::IParticleEmitter* em = _Divine->createBoxEmitter(
		irr::core::aabbox3d<irr::f32>(0,0,0,0,0,0),
		irr::core::vector3df(0.0001f,0.0004f,0.0001f),
		50,50,
		irr::video::SColor(10,255,255,255),
		irr::video::SColor(10,255,255,255),
		400,1100);
	em->setMinStartSize(irr::core::dimension2d<irr::f32>(0.1f, 0.1f));
	em->setMaxStartSize(irr::core::dimension2d<irr::f32>(2.f, 2.f));
	_Divine->setEmitter(em);
	em->drop();
	irr::scene::IParticleAffector* paf =
		_Divine->createFadeOutParticleAffector();
	_Divine->addAffector(paf);
	paf->drop();
	_Divine->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_Divine->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	_Divine->setMaterialTexture(0, _driver->getTexture(
		FILEPATH "media/fire/particlewhite.bmp"));
	_Divine->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	_Divine->setScale(irr::core::vector3df(0.00002, 0.000002, 0.00001));
}

void Light::DivineRemoveAnimation ()
{
	_DivineLight->removeAnimators();
}

void Light::createLightFloor ()
{
	_FloorLight =
		_sceneManager->addLightSceneNode(
			0, irr::core::vector3df(0,0,0),
			irr::video::SColorf(0.5f, 1.0f, 0.5f, 0.0f), 800.0f);
	irr::scene::ISceneNodeAnimator* anim =
		_sceneManager->createFlyCircleAnimator (
			irr::core::vector3df(50,300,0),190.0f, -0.003f);
	_FloorLight->addAnimator(anim);
	anim->drop();
	irr::scene::IBillboardSceneNode* bill =
		_sceneManager->addBillboardSceneNode(
			_FloorLight, irr::core::dimension2d<irr::f32>(60, 60));
	bill->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	bill->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	bill->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	bill->setMaterialTexture(0, _driver->getTexture(
		FILEPATH "media/fire/particlegreen.jpg"));
}

void Light::createSonny ()
{
	_Sonny = _sceneManager->addParticleSystemSceneNode(false);

	irr::scene::IParticleEmitter* em = _Sonny->createBoxEmitter(
		irr::core::aabbox3d<irr::f32>(0,0,0,0,0,0),
		irr::core::vector3df(0.0001f,0.0004f,0.0001f),
		40,40,
		irr::video::SColor(0,255,255,255),
		irr::video::SColor(0,255,255,255),
		800,2000,0,
		irr::core::dimension2df(3.f,3.f),
		irr::core::dimension2df(5.f,5.f));
	_Sonny->setEmitter(em);
	em->drop();
	irr::scene::IParticleAffector* paf = _Sonny->
		createFadeOutParticleAffector();
	_Sonny->addAffector(paf);
	paf->drop();
	_Sonny->setScale(irr::core::vector3df(0.02, 0.02, 0.01));
	_Sonny->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_Sonny->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	_Sonny->setMaterialTexture(0, _driver->getTexture(
		FILEPATH "media/fire/particlewhite.bmp"));
	_Sonny->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	_Sonny->setPosition(irr::core::vector3df(10.5, 5, 0));
}

void Light::createJetFire  (irr::scene::ISceneNode *mesh)
{
	_JetFireLight = _sceneManager->addLightSceneNode(0);
	irr::core::vector3df start = mesh->getPosition();
	start.Y += 5;
	irr::scene::IBillboardSceneNode* bill =
		_sceneManager->addBillboardSceneNode(
			_JetFireLight, irr::core::dimension2d<irr::f32>(2.5, 2.5));
	bill->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	bill->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	bill->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	bill->setMaterialTexture(0, _driver->getTexture(
		FILEPATH "media/fire/fireball.bmp"));
	bill->setPosition(start);
}

void Light::deleteSonny ()
{
}