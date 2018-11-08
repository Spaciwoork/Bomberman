/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** Created by MP,
*/

#include "Ia.hpp"

std::vector<std::pair<int, float>> IA::bombNear()
{
	int x = 0;
	int y = 0;
	int _x = round(_Axe.Z);
	int _y = round(_Axe.X);
	std::map<irr::core::vector2di, IObject *>::iterator it;
	IObject *elem;
	std::vector<std::pair<int, float>> bombs;

	while (y < _MapSize.second) {
		while (x < _MapSize.first) {
			it = _Map->find(irr::core::vector2di(y, x));
			if (it != _Map->end()) {
				elem = it->second;
				if (elem != NULL && elem->getType() == IObject::Type::T_BOMB) {
					if (x == _x && fabs(y - _y) <= elem->getPower())
					{
						if (y > _y)
							bombs.push_back(std::make_pair(IA::way::TOP, fabs(y - _y)));
						else
							bombs.push_back(std::make_pair(IA::way::BOTTOM, fabs(y - _y)));
					}
					else if (y == _y && fabs(x - _x) <= elem->getPower())
					{
						if (x > _x)
							bombs.push_back(std::make_pair(IA::way::LEFT, fabs(x - _x)));
						else
							bombs.push_back(std::make_pair(IA::way::RIGHT, fabs(x - _x)));
					}
				}
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (bombs);
}

void IA::Run(int dir)
{
	int first;
	std::vector<int>::iterator it;

	if (_prevMoves.size() >= 40) {
		first = _prevMoves.at(0);
		for (it = _prevMoves.begin(); it != _prevMoves.end() && *it == first; it++);
		if (it == _prevMoves.end()) {
			if (dir == LEFT)
				dir = TOP;
			else if (dir == TOP)
				dir = RIGHT;
			else if (dir == RIGHT)
				dir = BOTTOM;
			else if (dir == BOTTOM)
				dir = LEFT;
		}
	}
	switch (dir) {
		case TOP:
			Run_Up();
			break;
		case RIGHT:
			Run_Right();
			break;
		case BOTTOM:
			Run_Down();
			break;
		case LEFT:
			Run_Left();
			break;
	}
	_prevMoves.insert(_prevMoves.begin(), dir);
	if (_prevMoves.size() > 40)
		_prevMoves.pop_back();
}

bool IA::isBlocked(int _x, int _y)
{
	std::map<irr::core::vector2di, IObject *>::iterator it;
	IObject *elem;

	it = _Map->find(irr::core::vector2di(_y, _x));
	if (it != _Map->end()) {
		elem = it->second;
		if (elem == NULL || elem->getType() == IObject::Type::T_BONUS)
			return (false);
		else
			return (true);
	}
	return (true);
}

int *IA::getWayLength(int _x, int _y)
{
	int *wayLength = (int*)malloc(sizeof(int) * 4);
	int x;
	int y;

	for (int i = 0; i < 4; i++)
		wayLength[i] = 0;
	x = _x + 1;
	y = _y;
	while (isInMap(x, y) == true && isBlocked(x, y) == false) {
		wayLength[0]++;
		x++;
	}
	if (isInMap(x, y) == false || isCrate(x, y) == false)
		wayLength[0] = 17;
	x = _x;
	y = _y + 1;
	while (isInMap(x, y) == true && isBlocked(x, y) == false) {
		wayLength[1]++;
		y++;
	}
	if (isInMap(x, y) == false || isCrate(x, y) == false)
		wayLength[1] = 17;
	x = _x - 1;
	y = _y;
	while (isInMap(x, y) == true && isBlocked(x, y) == false) {
		wayLength[2]++;
		x--;
	}
	if (isInMap(x, y) == false || isCrate(x, y) == false)
		wayLength[2] = 17;
	x = _x;
	y = _y - 1;
	while (isInMap(x, y) == true && isBlocked(x, y) == false) {
		wayLength[3]++;
		y--;
	}
	if (isInMap(x, y) == false || isCrate(x, y) == false)
		wayLength[3] = 17;
	return (wayLength);
}

bool IA::isDangerous(int _x, int _y)
{
	int ret;
	int x;
	int y;

	x = _x + 1;
	y = _y;
	while (isInMap(x, y) == true && (ret = isBomb(x, y)) == 0)
		x++;
	if (abs(x - _x) <= ret || abs(y - _y) <= ret)
		return (true);
	x = _x;
	y = _y + 1;
	while (isInMap(x, y) == true && (ret = isBomb(x, y)) == 0)
		y++;
	if (abs(x - _x) <= ret || abs(y - _y) <= ret)
		return (true);
	x = _x - 1;
	y = _y;
	while (isInMap(x, y) == true && (ret = isBomb(x, y)) == 0)
		x--;
	if (abs(x - _x) <= ret || abs(y - _y) <= ret)
		return (true);
	x = _x;
	y = _y - 1;
	while (isInMap(x, y) == true && (ret = isBomb(x, y)) == 0)
		y--;
	if (abs(x - _x) <= ret || abs(y - _y) <= ret)
		return (true);
	return (false);
}

void IA::TryRun(int dir)
{
	int x = 0;
	int y = 0;
	int _x = round(_Axe.Z);
	int _y = round(_Axe.X);

	switch (dir) {
		case TOP:
			y = _y + 1;
			x = _x;
			break;
		case RIGHT:
			x = _x - 1;
			y = _y;
			break;
		case BOTTOM:
			y = _y - 1;
			x = _x;
			break;
		case LEFT:
			x = _x + 1;
			y = _y;
			break;
	}
	for (int i = 0; i < 2 && isBlocked(x, y) == true; i++) {
		switch (dir) {
			case TOP:
				dir = RIGHT;
				x = _x - 1;
				y = _y;
				break;
			case RIGHT:
				dir = BOTTOM;
				y = _y - 1;
				x = _x;
				break;
			case BOTTOM:
				dir = LEFT;
				x = _x + 1;
				y = _y;
				break;
			case LEFT:
				dir = TOP;
				y = _y + 1;
				x = _x;
				break;
		}
	}
	if (isBlocked(x, y)) {
		switch (dir) {
			case RIGHT:
				dir = LEFT;
				break;
			case LEFT:
				dir = RIGHT;
				break;
			case BOTTOM:
				dir = TOP;
				break;
			case TOP:
				dir = BOTTOM;
				break;
		}
	}
	Run(dir);
}

void IA::dodge_move(int direction)
{
	int _x = round(_Axe.Z);
	int _y = round(_Axe.X);
	int way;

	if (direction == TOP || direction == BOTTOM) {
		_x += 1;
		way = LEFT;
		if (isBlocked(_x, _y) == true) {
			_x -= 2;
			way = RIGHT;
		}
	} else {
		_y += 1;
		way = TOP;
		if (isBlocked(_x, _y) == true) {
			_y -= 2;
			way = BOTTOM;
		}
	}
	if (isBlocked(_x, _y) == true) {
		if (direction == TOP)
			way = BOTTOM;
		else if (direction == BOTTOM)
			way = TOP;
		else if (direction == LEFT)
			way = RIGHT;
		else
			way = LEFT;
	}
	TryRun(way);
}

int IA::dodge(std::vector<std::pair<int, float>> bombs)
{
	int directions[4] = {0, 0, 0, 0};
	std::pair<int, int> greatest = std::pair<int, int>(-1, -1);

	for (std::vector<std::pair<int, float>>::iterator it = bombs.begin(); it != bombs.end(); it++) {
		switch (it->first) {
			case IA::way::LEFT:	directions[0]++;
				break;
			case IA::way::TOP:	directions[1]++;
				break;
			case IA::way::RIGHT:	directions[2]++;
				break;
			case IA::way::BOTTOM:	directions[3]++;
				break;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (directions[i] > greatest.second && directions[i] != 0)
			greatest = std::make_pair(i, directions[i]);
	}
	if (greatest.second == -1)
		return (-1);
	dodge_move(greatest.first);
	return (0);
}

void IA::moveTo(std::pair<int, int> pos)
{
	int x = pos.first;
	int y = pos.second;
	int _x = round(_Axe.Z);
	int _y = round(_Axe.X);
	int way = BOTTOM;

	if (abs(x - _x) == abs(y - _y)) {
		if (isBlocked(_x, _y + 1) == true && isBlocked(_x, _y - 1) == true)
			way = RIGHT;
	}
	else if (abs(x - _x) > abs(y - _y))
		way = RIGHT;
	if (way == RIGHT) {
		if (x > _x)
			way = LEFT;
	} else if (way == BOTTOM) {
		if (y > _y)
			way = TOP;
	}
	TryRunOffensive(way);
}

int IA::pickPwUp()
{
	int x = 0;
	int y = 0;
	int _x = round(_Axe.Z);
	int _y = round(_Axe.X);
	std::map<irr::core::vector2di, IObject *>::iterator it;
	IObject *elem;
	std::vector<std::pair<int, int>> PwUps;
	std::tuple<int, int, int> distance = std::tuple<int, int, int>(-1, -1, -1);
	int tmp;

	while (y < _MapSize.second) {
		while (x < _MapSize.first) {
			it = _Map->find(irr::core::vector2di(y, x));
			if (it != _Map->end()) {
				elem = it->second;
				if (elem != NULL && elem->getType() == IObject::Type::T_BONUS)
					PwUps.push_back(std::make_pair(x, y));
			}
			x++;
		}
		x = 0;
		y++;
	}
	if (PwUps.empty() == true)
		return (-1);
	for (auto it = PwUps.begin(); it != PwUps.end(); it++) {
		x = it->first;
		y = it->second;
		tmp = abs(x - _x) + abs(y - _y);
		if (tmp < std::get<2>(distance) || std::get<0>(distance) == -1)
			distance = std::make_tuple(x, y, tmp);
	}
	if (std::get<2>(distance) <= 2 && (isCrate(std::get<0>(distance) + 1, std::get<1>(distance)) == true || isCrate(std::get<0>(distance) - 1, std::get<1>(distance)) == true || isCrate(std::get<0>(distance), std::get<1>(distance) + 1) == true || isCrate(std::get<0>(distance), std::get<1>(distance) - 1) == true))
		Put_Bomb();
	else if (std::get<2>(distance) <= 2)
		moveTo(std::make_pair(x, y));
	else
		return (-1);
	return (0);
}

int IA::isBomb(int _x, int _y)
{
	std::map<irr::core::vector2di, IObject *>::iterator it;
	IObject *elem;

	it = _Map->find(irr::core::vector2di(_y, _x));
	if (it != _Map->end()) {
		elem = it->second;
		if (elem == NULL)
			return (0);
		else if (elem->getType() == IObject::Type::T_BOMB)
			return (elem->getPower());
		else
			return (0);
	}
	return (0);
}

bool IA::isCrate(int _x, int _y)
{
	std::map<irr::core::vector2di, IObject *>::iterator it;
	IObject *elem;

	it = _Map->find(irr::core::vector2di(_y, _x));
	if (it != _Map->end()) {
		elem = it->second;
		if (elem == NULL)
			return (false);
		else if (elem->getType() == IObject::Type::T_CRATE)
			return (true);
		else
			return (false);
	}
	return (false);
}

bool IA::isInMap(int _x, int _y)
{
	int x = _MapSize.first;
	int y = _MapSize.second;

	if (_x >= 0 && _x < x && _y >= 0 && _y < y)
		return (true);
	return (false);
}

int IA::breakCrates()
{
	int _x = round(_Axe.Z);
	int _y = round(_Axe.X);
	int x = _x + 2;
	int y = _y + 2;
	std::vector<std::tuple<int, int, int>> crates;

	while (y >= _y - 2) {
		while (x >= _x - 2) {
			if (isInMap(x, y) == true && isCrate(x, y) == true)
				crates.push_back(std::make_tuple(x, y, abs(x - _x) + abs(y - _y)));
			x--;
		}
		x = _x + 2;
		y--;
	}
	return (0);
}

void IA::TryRunOffensive(int dir)
{
	int x = 0;
	int y = 0;
	int _x = round(_Axe.Z);
	int _y = round(_Axe.X);

	switch (dir) {
		case TOP:
			y = _y + 1;
			x = _x;
			break;
		case RIGHT:
			x = _x - 1;
			y = _y;
			break;
		case BOTTOM:
			y = _y - 1;
			x = _x;
			break;
		case LEFT:
			x = _x + 1;
			y = _y;
			break;
	}
	for (int i = 0; i < 2 && (isBlocked(x, y) == true || isDangerous(x, y) == true); i++) {
		switch (dir) {
			case TOP:
				dir = RIGHT;
				x = _x - 1;
				y = _y;
				break;
			case RIGHT:
				dir = BOTTOM;
				y = _y - 1;
				x = _x;
				break;
			case BOTTOM:
				dir = LEFT;
				x = _x + 1;
				y = _y;
				break;
			case LEFT:
				dir = TOP;
				y = _y + 1;
				x = _x;
				break;
		}
	}
	if (isBlocked(x, y) || isDangerous(x, y) == true) {
		switch (dir) {
			case RIGHT:
				dir = LEFT;
				break;
			case LEFT:
				dir = RIGHT;
				break;
			case BOTTOM:
				dir = TOP;
				break;
			case TOP:
				dir = BOTTOM;
				break;
		}
	}
	if (isDangerous(x, y == false))
		Run(dir);
}

int IA::checkInactivity()
{
	int x = round(_Axe.Z);
	int y = round(_Axe.X);
	std::pair<int, int> pos(x, y);
	std::pair<int, int> tmp;
	std::vector<std::pair<int, int>>::iterator it;
	int ret = -1;

	if (_prevPos.size() >= 40) {
		tmp = _prevPos.at(0);
		for (it = _prevPos.begin(); it != _prevPos.end()
			&& it->first <= tmp.first + 1 && it->first >= tmp.first - 1
			&& it->second <= tmp.second + 1 && it->second >= tmp.second - 1;
			it++);
		if (it == _prevPos.end()) {
			Put_Bomb();
			ret = 0;
		}
	}
	_prevPos.insert(_prevPos.begin(), pos);
	if (_prevPos.size() > 40)
		_prevPos.pop_back();
	return (ret);
}

void IA::wander()
{
	int _x = round(_Axe.Z);
	int _y = round(_Axe.X);
	int *wayLength = getWayLength(_x, _y);
	int len = 17;
	int dir;

	for (int i = 0; i < 4; i++) {
		if (wayLength[i] <= len) {
			len = wayLength[i];
			dir = i;
		}
	}
	if (len == 0)
		Put_Bomb();
	else {
		if (len == 17)
			Put_Bomb();
		else
			TryRunOffensive(dir);
	}
}

void IA::handleEvent(EventReceiver *KeyReceive, const irr::f32 fdt, irr::scene::ITriangleSelector **selector)
{
	std::vector<std::pair<int, float>> bombs;
	int ret = -1;
	irr::core::vector3df old_pos = _Axe;

	Personage::First_Collision();
	(void)KeyReceive;
	CheckNomberBomb();
	_Selector = *selector;
	_SpeedMv = _Speed * fdt;
	bombs = bombNear();
	if (bombs.empty() == false)
		ret = dodge(bombs);
	if (ret == -1)
		ret = pickPwUp();
	if (ret == -1)
		wander();
	catchBonus(irr::core::vector3df(round(_Axe.X), round(_Axe.Y), _Axe.Z));
	setPos(_Axe, _Rotation);
	Personage::Check_goodPlace(old_pos);
}

IA::IA(std::pair<irr::video::IVideoDriver*, irr::scene::ISceneManager*> win_info,
	std::pair <int, int> info,
	std::map <irr::core::vector2di, IObject *> *Map, std::pair<int, float> MapSize)
		: Personage(win_info, info, Map), _MapSize(MapSize)
{}

IA::~IA()
{}