//
// EPITECH PROJECT, 2018
// Crate
// File description:
// Crate
//

#include "Bonus.hpp"
#include "Tools.hpp"


Bonus::Bonus(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
	     irr::scene::ITriangleSelector **selector, int effect)
	:IObject(true, true)
{
	if (driver == nullptr || sceneManager == nullptr)
		return ;
	int bonus_type;
	if (effect == -1)
		bonus_type = getTimeRand();
	else {
		if (effect == IObject::Effect::BOMB_UP){
			bonus_type = B_BOMB_UP;
		}
		if (effect == IObject::Effect::SPEED_UP){
			bonus_type = B_SPEED_UP;
		}
		if (effect == IObject::Effect::FIRE_UP){
			bonus_type = B_FIRE_UP;
		}
		if (effect == IObject::Effect::WALL_PASS){
			bonus_type = B_WALL_PASS;
		}
				
	}
	switch (bonus_type)
	{
		case B_BOMB_UP:
			_mesh = sceneManager->addAnimatedMeshSceneNode(
				sceneManager->getMesh(
					FILEPATH "media/Bonus/Bomb_up.obj")
				, 0, isDESTRandCATCH);
			_effect = Effect::BOMB_UP;
			break;
		case B_SPEED_UP:
			_mesh = sceneManager->addAnimatedMeshSceneNode(
				sceneManager->getMesh(
					FILEPATH "media/Bonus/Speed_up.obj"), 0,
				isDESTRandCATCH);
			_effect = Effect::SPEED_UP;
			break;
		case B_FIRE_UP:
			_mesh = sceneManager->addAnimatedMeshSceneNode(
				sceneManager->getMesh(
					FILEPATH "media/Bonus/Fire_up.obj")
				, 0, isDESTRandCATCH);
			_effect = Effect::FIRE_UP;
			break;
		case B_WALL_PASS:
			_mesh = sceneManager->addAnimatedMeshSceneNode(
				sceneManager->getMesh(
					FILEPATH "media/Bonus/Wall_walk.obj"), 0,
				isDESTRandCATCH);
			_effect = Effect::WALL_PASS;
			break;
		default:
			break;
	}
	_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_mesh->setScale(irr::core::vector3df(0.5, 0.5, 0.1));
	*selector = sceneManager->createTriangleSelector((
		irr::scene::IAnimatedMeshSceneNode*)_mesh);
	_mesh->setTriangleSelector(*selector);
	_type = IObject::Type::T_BONUS;
	_move = 0;
}

Bonus::~Bonus()
{
}

int Bonus::getTimeRand()
{
	int rd = 0;
	static int save[1];
	static int old = 0;
	int x = 0;

	x = rand() % 2 + 0;
	rd = rand() % 4 + 0;
	while (rd == save[x]  || rd == old) {
		rd = rand() % 4 + 0;
		std::this_thread::sleep_for(std::chrono::microseconds(100000));
	}
	old = rd;
	save[x] = rd;
	return (rd);
}

void Bonus::frame(irr::f32 frameDeltaTime, irr::scene::ITriangleSelector **selector)
{
	(void)frameDeltaTime;
	_mesh->setRotation(irr::core::vector3df(0, _move, 0));
	_move += 5;
	(void)selector;
}

void Bonus::DropObject()
{
	music->play2D(FILEPATH "media/musics/Bonus.wav");
	_mesh->drop();
}
