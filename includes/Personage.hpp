/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** Created by MP,
*/

#ifndef PERSONAGE_HPP
# define PERSONAGE_HPP

#include <iostream>
#include <chrono>
#include <time.h>
#include <irrlicht/irrlicht.h>
#include <vector>
#include <map>
#include <climits>
#include <cstdint>
#include <thread>
#include <chrono>
#include <array>
#include "ElementType.hpp"
#include "EventReceiver.hpp"
#include "IObject.hpp"
#include "Fire.hpp"
#include "Bomb.hpp"

class Personage
{
	public:
	/*enum Direction
	{
		D_UPX,
		D_DOWNX,
		D_RIGHTZ,
		D_LEFTZ,
		D_NONE
	};*/

	enum Control
	{
		C_LEVER = 3,
		C_KEYBOARD2 = 2,
		C_KEYBOARD1 = 1
	};

	enum Color_PLAYER
	{
		YELLOW_PLAYER = 4,
		BLACK_PLAYER = 3,
		BLUE_PLAYER = 2,
		RED_PLAYER = 1
	};
	Personage(std::pair<irr::video::IVideoDriver*,
		irr::scene::ISceneManager*> win_info,
		  std::pair <int, int> info,
		std::map <irr::core::vector2di, IObject *> *Map);

	~Personage();
	void setPos (irr::core::vector3df ax, irr::core::vector3df rota);
	virtual void handleEvent (EventReceiver *KeyReceive, const irr::f32 fdt,
			  irr::scene::ITriangleSelector **_Selector);

	void setSelector(irr::scene::ITriangleSelector **selector);
	void setControler(int num_player);
	bool hasCollision(irr::core::vector3df dist);
	irr::scene::IAnimatedMeshSceneNode *getMesh();
	irr::core::vector3df getRotation();
	irr::core::vector3df getAxe();
	irr::core::vector3df getCamAxe();
	irr::core::vector3df getCamTarget();
	void Death(int cor);
	void Run_Left();
	void Run_Right();
	void Run_Up();
	void Run_Down();
	void RunPerso();

	void Put_Bomb();
	void Reach_PowerUp(irr::core::vector2di pos);
	void StarterPostion(int var);
	void Position_UpLeft();
	void Position_DownRight();
	void Position_UpRight();
	void Position_DownLeft();
	bool check_Collision(irr::core::vector2di pos);
	void Check_goodPlace(irr::core::vector3df old_pos);
	bool inBomb(IObject *tmp);
	IObject *getPositionObjectMap(irr::core::vector3df pos);
	void First_Collision();
	bool isSame(irr::core::vector3df axe, irr::core::vector3df pos);
	bool catchBonus(irr::core::vector3df dist);
	void check_endWallPass();
	void setAxe(irr::core::vector3df axe);
	void setRota (irr::core::vector3df rota);
	void setFramLoop(irr::u32 a, irr::u32 b);
	void Animation();
	void JoystickMovement (const irr::SEvent::SJoystickEvent & joystickData);
	void CheckNomberBomb();

	int getBombNomber();
	void setBombNomber(int nbr);

	void setWallPass(bool var);
	bool getWallPass();

	int getControl();

	int getFireUp();
	void setFireUp(int fire_up);

	bool getPutBomb();
	void setPutBomb(bool put_bomb);

	bool getIsMoving();
	void setIsMoving(bool ismoving);

	irr::u32 getSpeed();
	void setSpeed(irr::u32 speed);

	irr::u32 getSpeedMv ();
	void setSpeedMv (irr::u32 speedmv);

	void setScManager(irr::scene::ISceneManager *sc);
	std::vector <Bomb *> getBombs();
	void setBombs(std::vector <Bomb *> bomb);
	void setDriver(irr::video::IVideoDriver *dv);
	void setMap(std::map <irr::core::vector2di, IObject *> *map);
	void setPosBomb(irr::core::vector3df pos);
	irr::core::vector3df getPosBomb();

	int getInfoOne() const;
	int getInfoTwo() const;

	protected:
	int _Control;
	int _BombNomber;
	bool _WallPass;
	bool _inBomb;
	int _FireUp;
	bool _PutBomb;
	bool _isMoving;
	bool _Lever;
	irr::u32 _Speed;
	irr::f32 _SpeedMv;
	irr::core::vector3df _Axe;
	irr::core::vector3df _CamAxe;
	irr::core::vector3df _CamTarget;
	irr::core::vector3df _Rotation;
	irr::scene::IAnimatedMeshSceneNode *_Player;
	irr::scene::ISceneManager *_ScManager;
	std::map < irr::EKEY_CODE, void(Personage::*)() > _KeyTab;
	std::map <irr::core::vector2di, IObject *> *_Map;
	irr::video::IVideoDriver *_Driv;
	std::vector <Bomb *> _bombs;
	irr::scene::ITriangleSelector* _Selector;
	irr::core::vector3df _Pos_bomb;
	int _info_one;
	int _info_two;
	irrklang::ISound *_movSound;
	std::array<std::string, 2> _deathSound = { FILEPATH "media/musics/Mort1.wav", FILEPATH "media/musics/Mort2.wav" };
};

#endif /* !PERSONAGE_HPP */
