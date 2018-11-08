/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** Created by MP,
*/

#include "Personage.hpp"

Personage::Personage(std::pair<irr::video::IVideoDriver*, irr::scene::ISceneManager*> win_info,
		     std::pair <int, int> info,
	std::map <irr::core::vector2di, IObject *> *Map)
{
	_Map = Map;
	_Driv = win_info.first;
	_info_one = info.first;
	_info_two = info.second;
	_ScManager = win_info.second;
	irr::video::SMaterial material;
	_Player = _ScManager->addAnimatedMeshSceneNode(
		_ScManager->getMesh(FILEPATH "media/Bomberman/Bomberman.b3d"),
		0, isALIVE);
	_Player->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	switch (info.first) {
		case RED_PLAYER:
			material.setTexture(0, _Driv->getTexture(
				FILEPATH "media/Bomberman/Red_perso.png"));
			break;
		case BLACK_PLAYER:
			material.setTexture(0, _Driv->getTexture(
				FILEPATH "media/Bomberman/Black_perso.png"));
			break;
		case BLUE_PLAYER:
			material.setTexture(0, _Driv->getTexture(
				FILEPATH "media/Bomberman/Blue_perso.png"));
			break;
		case YELLOW_PLAYER:
			material.setTexture(0, _Driv->getTexture(
				FILEPATH "media/Bomberman/Yellow_perso.png"));
			break;
		default:
			break;
	}
	material.Lighting = false;
	material.NormalizeNormals = true;
	_Player->getMaterial(0) = material;
	_Player->setScale(irr::core::vector3df(0.15, 0.15, 0.15));
	_Player->setMD2Animation(irr::scene::EMAT_STAND);
	_Rotation = _Player->getRotation();
	StarterPostion(info.second);
	_Control = 0;
	material.Wireframe = true;
	_Selector = 0;
	setSpeed(3.5f);
	_inBomb = false;
	_Player->setFrameLoop(1, 11);
	_Lever = false;
	setWallPass(false);
	setBombNomber(1);
	setFireUp(1);
	setPosBomb(irr::core::vector3df(-10, -10, -10));
	setPutBomb(false);
	setIsMoving(false);
	_movSound = music->play2D(FILEPATH "media/musics/pas.wav", true, true);
}

Personage::~Personage()
{
	_Player->remove();
}

void Personage::setControler(int num_player)
{
	_Control = num_player;
	if (_Control == C_KEYBOARD1) {
		_KeyTab.insert(
			std::make_pair(irr::KEY_LEFT, &Personage::Run_Left));
		_KeyTab.insert(
			std::make_pair(irr::KEY_RIGHT, &Personage::Run_Right));
		_KeyTab.insert(std::make_pair(irr::KEY_UP, &Personage::Run_Up));
		_KeyTab.insert(std::make_pair(irr::KEY_DOWN, &Personage::Run_Down));
		_KeyTab.insert(
			std::make_pair(irr::KEY_RETURN, &Personage::Put_Bomb));
	}
	else if (_Control == C_KEYBOARD2) {
		_KeyTab.insert(
			std::make_pair(irr::KEY_KEY_Q, &Personage::Run_Left));
		_KeyTab.insert(
			std::make_pair(irr::KEY_KEY_D, &Personage::Run_Right));
		_KeyTab.insert(std::make_pair(irr::KEY_KEY_Z, &Personage::Run_Up));
		_KeyTab.insert(
			std::make_pair(irr::KEY_KEY_S, &Personage::Run_Down));
		_KeyTab.insert(
			std::make_pair(irr::KEY_SPACE, &Personage::Put_Bomb));
	}
	else if (_Control == C_LEVER) {
		_Lever = true;
	}
}

int Personage::getBombNomber()
{
	return (_BombNomber);
}


void Personage::setBombNomber(int nbr)
{
	_BombNomber = nbr;
}

void Personage::setWallPass(bool var)
{
	_WallPass = var;
}

bool Personage::getWallPass()
{
	return (_WallPass);
}

int Personage::getControl()
{
	return (_Control);
}

int Personage::getFireUp()
{
	return (_FireUp);
}

void Personage::setFireUp(int fire_up)
{
	_FireUp = fire_up;
}

bool Personage::getPutBomb()
{
	return (_PutBomb);
}

void Personage::setPutBomb(bool put_bomb)
{
	_PutBomb = put_bomb;
}

bool Personage::getIsMoving()
{
	return (_isMoving);
}

void Personage::setIsMoving(bool ismoving)
{
	_isMoving = ismoving;
}

irr::u32 Personage::getSpeed()
{
	return (_Speed);
}

void Personage::setSpeed(irr::u32 speed)
{
	_Speed = speed;
}

irr::u32  Personage::getSpeedMv ()
{
	return (_SpeedMv);
}

void Personage::setSpeedMv (irr::u32 speedmv)
{
	_SpeedMv = speedmv;
}

void Personage::setScManager(irr::scene::ISceneManager *sc)
{
	_ScManager = sc;
}

void Personage::setDriver(irr::video::IVideoDriver *dv)
{
	_Driv = dv;
}

void Personage::setMap(std::map <irr::core::vector2di, IObject *> *map)
{
	_Map = map;
}

std::vector <Bomb *> Personage::getBombs()
{
	return (_bombs);
}

void Personage::setBombs(std::vector <Bomb *> bomb)
{
	_bombs = bomb;
}

void Personage::setAxe(irr::core::vector3df axe)
{
	_Axe = axe;
}

void Personage::setFramLoop(irr::u32 a, irr::u32 b)
{
	_Player->setFrameLoop(a, b);
}

irr::core::vector3df Personage::getPosBomb()
{
	return (_Pos_bomb);
}

void Personage::setPosBomb(irr::core::vector3df pos)
{
	_Pos_bomb = pos;
}

void Personage::setSelector(irr::scene::ITriangleSelector **selector)
{
	*selector = _ScManager->createTriangleSelector(_Player);
	_Player->setTriangleSelector(*selector);
}

irr::core::vector3df Personage::getCamAxe()
{
	return (_CamAxe);
}

irr::core::vector3df Personage::getCamTarget()
{
	return (_CamTarget);
}

irr::core::vector3df Personage::getAxe()
{
	return (_Axe);
}

irr::core::vector3df Personage::getRotation()
{
	return (_Rotation);
}

irr::scene::IAnimatedMeshSceneNode *Personage::getMesh()
{
	return (_Player);
}

void Personage::setPos (irr::core::vector3df ax, irr::core::vector3df rota)
{
	_Axe = ax;
	_Rotation = rota;
	_Player->setPosition(_Axe);
	_Player->setRotation(_Rotation);
}

void Personage::setRota (irr::core::vector3df rota)
{
	_Rotation = rota;
	_Player->setRotation(_Rotation);
}

IObject *Personage::getPositionObjectMap(irr::core::vector3df pos)
{
	IObject *tmp = 0;
	std::map<irr::core::vector2di, IObject*>::iterator iterator;
	irr::core::vector2di current_square = irr::core::vector2di(
		roundf(pos.X), roundf(pos.Z));

	iterator = _Map->find(current_square);
	if (iterator != _Map->end())
		return(tmp = iterator->second);
	return (tmp);
}

void Personage::Position_UpRight ()
{
	irr::core::vector2di var(0, 0);
	irr::core::vector2df axe(0, 16);
	int rd = 0;

	for (;  (*_Map)[irr::core::vector2di(0, std::floor(axe.Y))] == nullptr
		&& axe.Y > 14;  axe.Y -= 0.5)
			var.Y += 1;
	for (; (*_Map)[irr::core::vector2di(std::floor(axe.X), 16)] == nullptr
		 && axe.X < 2; axe.X += 0.5)
			var.X += 1;
	rd = rand() % 3;
	if (!rd)
		setPos(irr::core::vector3df(16, -0.5, 0),
		       irr::core::vector3df(0, 0, 0));
	else if (var.Y  > var.X || (rd == 1 && (var.Y == var.X)))
		setPos(irr::core::vector3df(std::floor(axe.Y), -0.5, 0),
		       irr::core::vector3df(0, 270, 0));
	else if (var.X  > var.Y || (rd == 2 && (var.Y == var.X)))
		setPos(irr::core::vector3df(16, -0.5, std::floor(axe.X)),
		       irr::core::vector3df(0, 0, 0));

}

void Personage::Position_DownRight()
{
	irr::core::vector2di var(0, 0);
	irr::core::vector2df axe(0, 0);
	int rd = 0;

	for (; (*_Map)[irr::core::vector2di(15, std::floor(axe.Y))] == nullptr
	       && axe.Y < 2; axe.Y += 0.5)
		var.Y += 1;
	for (; (*_Map)[irr::core::vector2di(std::floor(axe.X), 0)] == nullptr
	       && axe.X < 2; axe.X += 0.5)
		var.X += 1;
	rd = rand() % 3;
	if (!rd)
		setPos(irr::core::vector3df(0, -0.5, 0),
		       irr::core::vector3df(0, 60, 0));
	else if (var.Y  > var.X || (rd == 1 && (var.Y == var.X))) {
		setPos(irr::core::vector3df(std::floor(axe.Y), -0.5, 0),
		       irr::core::vector3df(0, 90, 0));
	}
	else if (var.X  > var.Y || (rd == 2 && (var.Y == var.X))){
		setPos(irr::core::vector3df(0, -0.5, std::floor(axe.X)),
		       irr::core::vector3df(0, 0, 0));
	}
}

void Personage::Position_UpLeft ()
{
	irr::core::vector2di var(0, 0);
	irr::core::vector2df axe(16, 16);
	int rd = 0;

	for (; (*_Map)[irr::core::vector2di(16, std::floor(axe.Y))] == nullptr
	       && axe.Y > 14; axe.Y -= 0.5)
		var.Y += 1;
	for (; (*_Map)[irr::core::vector2di(std::floor(axe.X), 0)] == nullptr
	       && axe.X > 14; axe.X -= 0.5)
		var.X += 1;
	rd = rand() % 3;
	if (!rd)
		setPos(irr::core::vector3df(16, -0.5, 16),
		       irr::core::vector3df(0, 180, 0));
	else if (var.Y  > var.X || (rd == 1 && (var.Y == var.X)))
		setPos(irr::core::vector3df(std::floor(axe.Y), -0.5, 16),
		       irr::core::vector3df(0, 270, 0));
	else if (var.X  > var.Y || (rd == 2 && (var.Y == var.X)))
		setPos(irr::core::vector3df(16, -0.5, std::floor(axe.X)),
		       irr::core::vector3df(0, 180, 0));
}

void Personage::Position_DownLeft()
{
	irr::core::vector2di var(0, 0);
	irr::core::vector2df axe(16, 0);
	int rd = 0;

	for (; (*_Map)[irr::core::vector2di(16, std::floor(axe.Y))] == nullptr
	       && axe.Y < 2; axe.Y += 0.5)
		var.Y += 1;
	for (; (*_Map)[irr::core::vector2di(std::floor(axe.X), 0)] == nullptr
	       && axe.X > 14; axe.X -= 0.5)
		var.X += 1;
	rd = rand() % 3;
	if (!rd)
		setPos(irr::core::vector3df(0, -0.5, 16),
		       irr::core::vector3df(0, 140, 0));
	else if (var.Y  > var.X || (rd == 1 && (var.Y == var.X)))
		setPos(irr::core::vector3df(std::floor(axe.Y), -0.5, 16),
		       irr::core::vector3df(0, 90, 0));
	else if (var.X  > var.Y || (rd == 2 && (var.Y == var.X)))
		setPos(irr::core::vector3df(0, -0.5, std::floor(axe.X)),
		       irr::core::vector3df(0, 180, 0));
}

void Personage::StarterPostion (int var)
{
	switch (var)
	{
		case 0:
			Position_DownRight();
			break;
		case 1:
			Position_UpRight();
			break;
		case 2:
			Position_DownLeft();
			break;
		case 3:
			Position_UpLeft();
			break;
		default:
			break;
	}
}

void Personage::Death(int cor)
{
	_Player->setFrameLoop(66, 86);
	_Player->setAnimationSpeed(20);
	music->play2D(_deathSound[rand() % 2].c_str());
	switch (cor) {
		case 1:
			setPos(irr::core::vector3df(15.5, 1, 16),
			       irr::core::vector3df(0, 50, 0));
			break;
		case 2:
			setPos(irr::core::vector3df(15.5, 1, 0),
				       irr::core::vector3df(0, 140, 0));
			break;
		case 3:
			setPos(irr::core::vector3df(-0.9, 1, 15.8),
				       irr::core::vector3df(0,  300, 0));
			break;
		case 4:
			setPos(irr::core::vector3df(-1, 1, 1),
				       irr::core::vector3df(0, 230, 0));
			break;
		default:
			break;
	}
}

bool Personage::catchBonus(irr::core::vector3df dist)
{
	irr::scene::ISceneCollisionManager *collMan;
	irr::core::vector3df intersection;
	irr::core::triangle3df hitTriangle;
	irr::core::line3d <irr::f32> ray;
	irr::scene::ISceneNode * object;

	ray.start = _Player->getPosition();
	ray.end = dist;
	collMan = _ScManager->getSceneCollisionManager();
	object = collMan->getSceneNodeAndCollisionPointFromRay(
		ray, intersection, hitTriangle,	isINDESTRUCTIBLE, 0);
	if (object  && object->getID() == isDESTRandCATCH) {
		object->setID(ObjectType::isDESTROYED);
		Reach_PowerUp(irr::core::vector2di( object->getPosition().X,
						    object->getPosition().Z));
		return (true);
	}
	return (false);
}

bool Personage::hasCollision(irr::core::vector3df dist)
{

	IObject *tmp = getPositionObjectMap(dist);
	int type = -1;

	if (catchBonus(dist) == true)
		return (false);
	if (tmp && tmp->getType() != IObject::T_BONUS){
		type = tmp->getType();
		if (!((type == IObject::T_BOMB && _inBomb == true) ||
			    (type == IObject::T_CRATE && _WallPass == true)))
			return (true);
	}
	return (false);
}

void Personage::RunPerso()
{
	int frm = _Player->getFrameNr();

	if (_movSound->getIsPaused()) {
		_movSound->setIsPaused(false);
	}
	if ( frm < 11 || frm > 41) {
		_Player->setFrameLoop(11, 41);
		_Player->setAnimationSpeed(40);
	}
}

void Personage::Run_Left()
{
	float save = 0.0;
	irr::core::vector3df dist = _Axe;
	dist.Z = _Axe.Z + _SpeedMv < 16 ? _Axe.Z + _SpeedMv : _Axe.Z;
	save = dist.Z;
	dist.Z += 0.5;

	if (hasCollision(dist) == false) {
		_Axe.Z = save;
		RunPerso();
	}
	_CamAxe = _Axe;
	_CamTarget = _Axe;
	_CamAxe.Z -= 0.5;
	_CamTarget.Z += 2;
	_Rotation.Y = 180;
	_isMoving = true;
}

void Personage::Run_Right()
{
	float save = 0.0;
	irr::core::vector3df dist = _Axe;
	dist.Z = _Axe.Z - _SpeedMv > 0 ? _Axe.Z - _SpeedMv : _Axe.Z;
	save = dist.Z;
	dist.Z -= 0.5;

	if (hasCollision(dist) == false) {
		_Axe.Z = save;
		RunPerso();
	}
	_CamAxe = _Axe;
	_CamTarget = _Axe;
	_CamAxe.Z += 0.5;
	_CamTarget.Z -= 2;
	_Rotation.Y = 0;
	_isMoving = true;
}

void Personage::Run_Up()
{
	float save = 0.0;
	irr::core::vector3df dist = _Axe;
	dist.X = _Axe.X + _SpeedMv < 16 ? _Axe.X + _SpeedMv : _Axe.X;
	save = dist.X;
	dist.X += 0.5;

	if (hasCollision(dist) == false) {
		_Axe.X = save;
		RunPerso();
	}
	_CamAxe = _Axe;
	_CamTarget = _Axe;
	_CamAxe.X += -0.5;
	_CamTarget.X += 2;
	_Rotation.Y = 270;
	_isMoving = true;
}

void Personage::Run_Down()
{
	float save = 0.0;
	irr::core::vector3df dist = _Axe;
	dist.X = _Axe.X - _SpeedMv > 0 ? _Axe.X - _SpeedMv : _Axe.X;
	save = dist.X;
	dist.X -= 0.5;

	if (hasCollision(dist) == false) {
		_Axe.X = save;
		RunPerso();
	}
	_CamAxe = _Axe;
	_CamTarget = _Axe;
	_CamAxe.X += 0.5;
	_CamTarget.X -= 2;
	_Rotation.Y = 90;
	_isMoving = true;
}

bool isInMap(std::map<irr::core::vector2di, IObject*> *map, Bomb *object)
{
	for (std::map <irr::core::vector2di, IObject *>::iterator it = (*map).begin();
             it!=(*map).end(); ++it){
		if (it->second == object){
			return (true);
		}
	}
	return (false);
}

void Personage::Put_Bomb()
{
	Bomb *bomb;
       irr::core::vector3df pos_bomb = _Axe;

       pos_bomb.X = roundf(pos_bomb.X);
       pos_bomb.Y = 0;
       pos_bomb.Z = roundf(pos_bomb.Z);
       if ((int)_bombs.size() < _BombNomber){
	       if ((*_Map)[irr::core::vector2di(
	       	pos_bomb.X, pos_bomb.Z)] == nullptr){
		       bomb = new Bomb(_Driv, _ScManager, &_Selector, _FireUp);
		       bomb->setPosition(pos_bomb);
		       _bombs.push_back(bomb);
		       (*_Map)[irr::core::vector2di(
		       	pos_bomb.X, pos_bomb.Z)] = bomb;
	       }
       }
	_Pos_bomb = pos_bomb;
	_PutBomb = true;
}

void Personage::Reach_PowerUp(irr::core::vector2di pos)
{
	IObject *tmp;
	std::map<irr::core::vector2di, IObject*>::iterator iterator;

	iterator = _Map->find(pos);
	if (iterator != _Map->end()) {
		tmp = iterator->second;
		music->play2D(FILEPATH "media/musics/bonus.wav");
		switch (tmp->getEffect())
		{
			case  IObject::Effect::BOMB_UP:
				setBombNomber(_BombNomber +  1);
				break;
			case IObject::Effect::SPEED_UP:
				setSpeed(_Speed + 1.f);
				break;
			case IObject::Effect::FIRE_UP:
				setFireUp(_FireUp + 1);
				break;
			case IObject::Effect::WALL_PASS:
				setWallPass(true);
				break;
			default:
				break;
		}
	}

}

bool Personage::isSame(irr::core::vector3df axe, irr::core::vector3df pos)
{
	if ((roundf(axe.Z) == roundf(pos.Z)) &&
	    (roundf(axe.X) == roundf(pos.X))) {
		return (true);
	}
	return (false);
}

void Personage::First_Collision()
{
	IObject *tmp = getPositionObjectMap(_Axe);
	static int WallPass_Used = 0;
	irr::core::vector3df new_bomb;
	int type = -1;

	if (tmp){
		new_bomb = tmp->getMesh()->getPosition();
		type = tmp->getType();
		if (type == IObject::T_BOMB &&
		    isSame(new_bomb, _Axe) == true &&
			isSame(new_bomb, _Pos_bomb) == true) {
			_inBomb = true;
			return;
		}
		else if (type == IObject::T_CRATE){
			if (isSame(new_bomb, _Axe) == true) {
				_WallPass = true;
				WallPass_Used++;
				return;
			}
		}
	}
	_inBomb = false;
	if (_WallPass == true && WallPass_Used > 0) {
		_WallPass = false;
		WallPass_Used = 0;
	}
}

void Personage::Check_goodPlace(irr::core::vector3df old_pos)
{
	IObject *tmp = getPositionObjectMap(_Axe);
	int type = -1;

	if (tmp && tmp->getType() != IObject::T_BONUS){
		type = tmp->getType();
		if ((type == IObject::T_BOMB && _inBomb == true) ||
			(type == IObject::T_CRATE && _WallPass == true))
			setPos(_Axe, _Rotation);
		else {
			_Axe = old_pos;
		}
	}
	else {
		setPos(_Axe, _Rotation);
	}
	setRota (_Rotation);
}

void Personage::CheckNomberBomb()
{
	for (size_t i = 0; i < _bombs.size(); i++) {
		if (isInMap(_Map, _bombs[i]) == false)
			_bombs.erase(_bombs.begin() + i);
		else
			i++;
	}
}

void Personage::handleEvent (EventReceiver *KeyReceive, const irr::f32 fdt,
			     irr::scene::ITriangleSelector **selector)
{
	irr::core::vector3df old_pos = _Axe;

	First_Collision();
	CheckNomberBomb();
	_Selector = *selector;
	_SpeedMv = irr::f32(_Speed * fdt);
	for (std::map<irr::EKEY_CODE,
		void (Personage::*) ()>::iterator it = _KeyTab.begin();
	     it != _KeyTab.end(); it++) {
		if (KeyReceive->IsKeyDown(it->first)) {
			if (_KeyTab.at(it->first)) {
				(this->*_KeyTab.at(it->first))();
				break;
			}
			*selector = _Selector;
		}
		else
			_isMoving = false;
	}
	if (_isMoving != true &&
	    (_Player->getFrameNr() < 96 || _Player->getFrameNr() > 121)) {
		_Player->setFrameLoop(96, 121);
		_movSound->setIsPaused(true);
	}
	Check_goodPlace(old_pos);
}

int Personage::getInfoOne() const
{
	return (_info_one);
}

int Personage::getInfoTwo() const
{
	return (_info_two);
}
