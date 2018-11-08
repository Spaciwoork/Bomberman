//
// EPITECH PROJECT, 2018
// Crate
// File description:
// Crate
//

#include "Skybox.hpp"
#include "Tools.hpp"

Skybox::Skybox(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager)
	:IObject(true, true)
{
	if (driver == nullptr || sceneManager == nullptr)
		return ;
	irr::video::E_TEXTURE_CLAMP texture = irr::video::E_TEXTURE_CLAMP::ETC_CLAMP_TO_EDGE;

	_mesh = sceneManager->addEmptySceneNode();
	_mesh->setPosition(irr::core::vector3df(10,0,15));
	_mesh->setScale(irr::core::vector3df(1000,1000,1000));
	_mesh->setRotation(irr::core::vector3df(0,0,-45));

	_sky1 = sceneManager->addAnimatedMeshSceneNode(
		sceneManager->getMesh(FILEPATH "media/skybox/square.obj"));
        _sky1->setMaterialTexture(0,
				  driver->getTexture(""
			 FILEPATH "media/skybox/sky/skyrender0003.bmp"));
        _sky1->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_sky1->getMaterial(0).TextureLayer->TextureWrapU = texture;
	_sky1->getMaterial(0).TextureLayer->TextureWrapV = texture;
	
	_sky1->setPosition(irr::core::vector3df(0,0.5,0));
	_sky1->setRotation(irr::core::vector3df(180,180,0));
	_sky1->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);


	_sky2 = sceneManager->addAnimatedMeshSceneNode(
		sceneManager->getMesh(FILEPATH "media/skybox/square.obj"));
        _sky2->setMaterialTexture(0,
				  driver->getTexture(FILEPATH "media/skybox/sky/skyrender0006.bmp"));
        _sky2->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_sky2->getMaterial(0).TextureLayer->TextureWrapU = texture;
	_sky2->getMaterial(0).TextureLayer->TextureWrapV = texture;
	_sky2->setPosition(irr::core::vector3df(0,-0.5,0));
	_sky2->setRotation(irr::core::vector3df(0,90+90,0));
	_sky2->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);

	
	_sky3 = sceneManager->addAnimatedMeshSceneNode(
		sceneManager->getMesh(FILEPATH "media/skybox/square.obj"));
        _sky3->setMaterialTexture(0,
				  driver->getTexture(
				  	FILEPATH "media/skybox/sky/skyrender0001.bmp"));
        _sky3->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_sky3->getMaterial(0).TextureLayer->TextureWrapU = texture;	
	_sky3->getMaterial(0).TextureLayer->TextureWrapV = texture;
	_sky3->setPosition(irr::core::vector3df(0.5,0,0));
	_sky3->setRotation(irr::core::vector3df(0,-90,90));
	_sky3->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);

	_sky4 = sceneManager->addAnimatedMeshSceneNode(
		sceneManager->getMesh(FILEPATH "media/skybox/square.obj"));
        _sky4->setMaterialTexture(0,
				  driver->getTexture(
				  	FILEPATH "media/skybox/sky/skyrender0004.bmp"));
        _sky4->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_sky4->getMaterial(0).TextureLayer->TextureWrapU = texture;
	_sky4->getMaterial(0).TextureLayer->TextureWrapV = texture;
	_sky4->setPosition(irr::core::vector3df(-0.5,0,0));
	_sky4->setRotation(irr::core::vector3df(0,90,-90));
	_sky4->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);


	_sky5 = sceneManager->addAnimatedMeshSceneNode(
		sceneManager->getMesh(FILEPATH "media/skybox/square.obj"));
        _sky5->setMaterialTexture(0,
				  driver->getTexture(
				  	FILEPATH "media/skybox/sky/skyrender0005.bmp"));
        _sky5->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_sky5->getMaterial(0).TextureLayer->TextureWrapU = texture;
	_sky5->getMaterial(0).TextureLayer->TextureWrapV = texture;
	_sky5->setPosition(irr::core::vector3df(0.0,0.0,0.5));
	_sky5->setRotation(irr::core::vector3df(-90,0,180));
	_sky5->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);

	_sky6 = sceneManager->addAnimatedMeshSceneNode(
		sceneManager->getMesh(FILEPATH "media/skybox/square.obj"));
        _sky6->setMaterialTexture(0,
				  driver->getTexture(
				  	FILEPATH "media/skybox/sky/skyrender0002.bmp"));
        _sky6->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_sky6->getMaterial(0).TextureLayer->TextureWrapU = texture;
	_sky6->getMaterial(0).TextureLayer->TextureWrapV = texture;
	_sky6->setPosition(irr::core::vector3df(0.0,0.0,-0.5));
	_sky6->setRotation(irr::core::vector3df(90,0,0));
	_sky6->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);

	_mesh->addChild(_sky1);
	_mesh->addChild(_sky2);
	_mesh->addChild(_sky3);
	_mesh->addChild(_sky4);
	_mesh->addChild(_sky5);
	_mesh->addChild(_sky6);
}

void Skybox::frame(irr::f32 frameDeltaTime, irr::scene::ITriangleSelector **selector)
{
	static float count = 0;
	(void)frameDeltaTime;
	(void)selector;
	_mesh->setRotation(irr::core::vector3df(0,count,-45));
	count += 0.025;
}

Skybox::~Skybox()
{
}
