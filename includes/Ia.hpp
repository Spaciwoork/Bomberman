/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Ia
*/

#include "Personage.hpp"
#include <cmath>
#include <algorithm>
#include <tuple>

#ifndef IA_HPP
#define IA_HPP

class IA : public Personage
{
	public:
		enum way {
			LEFT = 0,
			TOP = 1,
			RIGHT = 2,
			BOTTOM = 3
		};
	public:
		IA(std::pair<irr::video::IVideoDriver*, irr::scene::ISceneManager*> win_info,
		  std::pair <int, int> info,
		std::map <irr::core::vector2di, IObject *> *Map, std::pair<int, float> MapSize);
		~IA();
		virtual void handleEvent(EventReceiver *, const irr::f32, irr::scene::ITriangleSelector **);
		std::vector<std::pair<int, float>> bombNear();
		int dodge(std::vector<std::pair<int, float>>);
		void dodge_move(int);
		void Run(int);
		bool isBlocked(int, int);
		int pickPwUp();
		void moveTo(std::pair<int, int>);
		void TryRun(int);
		int breakCrates();
		bool isCrate(int, int);
		bool isInMap(int, int);
		int safePutBomb();
		void wander();
		int *getWayLength(int _x, int _y);
		void TryRunOffensive(int);
		bool isDangerous(int _x, int _y);
		int isBomb(int _x, int _y);
		int checkInactivity();
	protected:
		std::pair<int, float> _MapSize;
		std::vector<int> _prevMoves;
		std::vector<std::pair<int, int>> _prevPos;
};

#endif /* !IA_HPP */