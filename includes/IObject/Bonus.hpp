//
// EPITECH PROJECT, 2018
// Crate
// File description:
// Crate
//

#ifndef BONUS_HPP_
# define BONUS_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <irrlicht/irrlicht.h>
#include <irrKlang/irrKlang.h>
#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include "IObject.hpp"

class Bonus : public IObject
{
	public:
	enum BonusType
	{
		B_BOMB_UP = 0,
		B_SPEED_UP = 1,
		B_FIRE_UP = 2,
		B_WALL_PASS = 3,
		B_NOTHING = -1
	};
	Bonus(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
	      irr::scene::ITriangleSelector **selector, int effect = -1);
	virtual ~Bonus();
	virtual void frame(irr::f32 frameDeltaTime, irr::scene::ITriangleSelector **selector);
	virtual void DropObject();
	int getTimeRand();

	private:
	int _move;
};

extern irrklang::ISoundEngine *music;

#endif
