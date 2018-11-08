/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by MP,
*/

#ifndef LIGHT_HPP
# define LIGHT_HPP

#include <iostream>
#include <irrlicht/irrlicht.h>

class Light
{
	public:
	Light(irr::scene::ISceneManager *sceneManager,
	      irr::video::IVideoDriver *_driver);
	~Light();
	void createDivine(irr::scene::ISceneNode *mesh);
	void createLightDivine(irr::scene::ISceneNode *mesh);
	void createLightFloor();
	void createSonny();
	void createJetFire(irr::scene::ISceneNode *mesh);
	void createjetFireLight (irr::scene::ISceneNode *mesh);
	void deletteLightDivine();
	void deleteLightFloor();
	void deleteDivine();
	void deleteSonny();
	void DivineRemoveAnimation();

	protected:
	irr::scene::ISceneNode* _DivineLight;
	irr::scene::ISceneNode* _JetFireLight;
	irr::scene::ILightSceneNode* _FloorLight;
	irr::scene::ISceneNodeAnimator* _AnimDivine;
	irr::video::IVideoDriver *_driver;
	irr::scene::ISceneManager *_sceneManager;
	irr::scene::IParticleSystemSceneNode* _Divine;
	irr::scene::IParticleSystemSceneNode* _JetFire;
	irr::scene::IParticleSystemSceneNode* _Sonny;
};

#endif /* !CPP_INDIE_STUDIO_LIGHT_HPP */
