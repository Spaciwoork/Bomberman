/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by MP,
*/

#include "Death_Ghosts.hpp"
#include "Tools.hpp"

Death_Ghosts::Death_Ghosts(irr::video::IVideoDriver *driver,
	     irr::scene::ISceneManager *sceneManager, irr::core::vector3df pos)
{
	int sec_rd = -1;
	int rd = rand() % 4;

	if (rd == 0 || rd == 3) {
		_Mesh = sceneManager->addAnimatedMeshSceneNode(
			sceneManager->getMesh(
				FILEPATH "media/Skeleton Ghost/Skeleton Ghost.obj"));
		sec_rd = rand() % 6;
		switch (sec_rd)
		{
			case 0:
				_Mesh->setMaterialTexture(
					0, driver->getTexture(
						FILEPATH "media/Skeleton Ghost/Textures/"
						"skul_0.png"));
				break;
			case 1:
				_Mesh->setMaterialTexture(
					0, driver->getTexture(
						FILEPATH "media/Skeleton Ghost/Textures/"
						"skul_1.png"));
				break;
			case 2:
				_Mesh->setMaterialTexture(
					0, driver->getTexture(
						FILEPATH "media/Skeleton Ghost/Textures/"
						"skul_2.png"));
				break;
			case 3:
				_Mesh->setMaterialTexture(
					0, driver->getTexture(
						FILEPATH "media/Skeleton Ghost/Textures/"
						"skul_3.png"));
				break;
			case 4:
				_Mesh->setMaterialTexture(
					0, driver->getTexture(
						FILEPATH "media/Skeleton Ghost/Textures/"
						"skul_4.png"));
				break;
			case 5:
				_Mesh->setMaterialTexture(
					0, driver->getTexture(
						FILEPATH "media/Skeleton Ghost/Textures/"
						"skul_5.png"));
				break;
			default:
				break;
		}
		_Mesh->setScale(irr::core::vector3df(0.3, 0.3, 0.3));
		_Mesh->setPosition(irr::core::vector3df(pos));
	}
	else if (rd == 1)
	{
		_Mesh = sceneManager->addAnimatedMeshSceneNode(
			sceneManager->getMesh(FILEPATH "media/Real Ghost/"
					      "Real Ghost.obj"));
		sec_rd = rand() % 2;
		if (!sec_rd)
			_Mesh->setMaterialTexture(
				0, driver->getTexture(FILEPATH "media/"
			  "Real Ghost/Image_2D_0311_0002.png"));
		else
			_Mesh->setMaterialTexture(
				0, driver->getTexture(FILEPATH "media/Real Ghost/"
			  "Image_2D_0325_0004.png"));
		_Mesh->setScale(irr::core::vector3df(0.040, 0.040, 0.040));
		_Mesh->setPosition(irr::core::vector3df(pos));
	}
	else if (rd == 2)
	{
		_Mesh = sceneManager->addAnimatedMeshSceneNode(
			sceneManager->getMesh(FILEPATH "media/Death Ninja/"
			 "Death Ninja.obj"));
		sec_rd = rand() % 2;
		if (!sec_rd)
			_Mesh->setMaterialTexture(
				0, driver->getTexture(FILEPATH "media/Death Ninja/"
			  "Textures/Death Ninja Body Texture.png"));
		else
			_Mesh->setMaterialTexture(
				0, driver->getTexture(FILEPATH "media/Death Ninja/"
			  "Textures/Sythe Texture.png'"));
		_Mesh->setScale(irr::core::vector3df(0.1, 0.1, 0.1));
		_Mesh->setPosition(irr::core::vector3df(pos));
	}
	_Mesh->setRotation(irr::core::vector3df(-40, 270, 0));
}

Death_Ghosts::~Death_Ghosts()
{
}

irr::scene::IAnimatedMeshSceneNode *Death_Ghosts::getMesh()
{
	return (_Mesh);
}

void Death_Ghosts::run_out ()
{
	_Mesh->remove();
}