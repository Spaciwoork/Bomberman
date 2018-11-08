/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** 
*/

#ifndef BOMB_HPP
#define BOMB_HPP

#include <iostream>
#include <thread>
#include <array>
#include <irrlicht/irrlicht.h>
#include <irrKlang/irrKlang.h>
#include "Fire.hpp"
#include "Tools.hpp"
#include "IObject.hpp"

class Bomb : public IObject
{
	public:
	Bomb(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
	     irr::scene::ITriangleSelector **selector, int power);
	virtual ~Bomb();
	void runAction(irr::scene::ITriangleSelector* selector);
	virtual void DropObject();
	void setPosition(irr::core::vector3df pos);
	void runAction(irr::scene::ITriangleSelector **selector, irr::f32 fdt);

	protected:
	irr::video::IVideoDriver *_Driv;
	irr::scene::ISceneManager *_ScManager;
	irr::f32 _fdt = 0.0;
	bool _has_exploded;
	irr::f32 _timer;
	irr::scene::ITriangleSelector **_Selector;
	irr::scene::IParticleSystemSceneNode* _Particle;
	std::array<std::string, 5> _explosions = { FILEPATH "media/musics/Explosion1.wav", FILEPATH "media/musics/Explosion2.wav", FILEPATH "media/musics/Explosion3.wav", FILEPATH "media/musics/Explosion4.wav", FILEPATH "media/musics/Explosion5.wav" };

	virtual void frame(irr::f32 frameDeltaTime, irr::scene::ITriangleSelector **selector);
	//irr::scene::IAnimatedMeshSceneNode *_Node;
	virtual void setEffect(const Effect effect);
	virtual Effect getEffect();
	void explode();
	void setTimer(const irr::f32 timer);
	
};

extern irrklang::ISoundEngine *music;

#endif /* !BOMB_HPP */
