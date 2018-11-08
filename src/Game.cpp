//
// EPITECH PROJECT, 2018
// Game
// File description:
// Game
//

#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include "Game.hpp"

Game::Game(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, Config &config)
{
	_device = device;
	_driver = driver;
	_upload = false;
	_MyEvent = new EventReceiver();
	_device->setEventReceiver(_MyEvent);
	_path_obj_wall = config.getPathWall();
	_path_obj_crate = config.getPathCube();
	_musicGame = music->play2D(FILEPATH "media/musics/game.wav", true, false, true);
	_musicGame->setVolume(0.6);
	_x = 16;
	_y = 16;
	if (_x % 2 == 0)
		_x++;
	if (_y % 2 == 0)
		_y++;
	_noise = new Noise(_x * 10 + 1, _y * 10 + 1, 128, 8);
	srand(time(NULL));
	_driver = _device->getVideoDriver();
        _sceneManager = _device->getSceneManager();
	_nbr_bonus = 10;
	addLights();
	_skybox = new Skybox(_driver, _sceneManager);
	_square = _sceneManager->addAnimatedMeshSceneNode(
                _sceneManager->getMesh(FILEPATH "media/ground/ground.obj"));
	_square->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_square->setScale(irr::core::vector3df(_x,0,_y));
	_square->setPosition(irr::core::vector3df((float)_x / 2 - 0.5,-0.5,(float)_y / 2 - 0.5));
	_Selector = 0;
	_Solo = false;
	_Death_nbr = 0;
	_NoFighter = false;
	_Pause = false;
	_Count_end = 0;
	_Light = new Light(_sceneManager, _driver);
	_MenuBack = false;
	addObjects(config);
	_Count_timer = 0;
	_Claps = false;
}


std::string Convert1(const std::wstring& WS)
// ------ conversion using the wcstombs function 
{
  const unsigned int wlen = WS.length();
  char *buf;
  buf = (char *)malloc(wlen * sizeof(std::wstring::value_type) + 1);
  const int res = std::wcstombs(buf, WS.c_str(), sizeof(buf));
  return (res >= 0) ? buf : "?";
}

void Game::addObjects(Config &config)
{
	_Cam = new Camera(_sceneManager, irr::core::vector3df(_x, _y, _y), _Solo);
	std::wstring tmp = config.getSavePlay();
	std::string tmp2 = Convert1(tmp);
	if (tmp2 != "?"){
		loadMap(FILEPATH "save/" + tmp2);
		_file_saving_name = FILEPATH "save/" + tmp2;
		return ;
	} else {
		int nbr;
		nbr = stoi(Tools::getFile(FILEPATH "media/conf/game.conf"));
		nbr++;
		_file_saving_name = FILEPATH "save/map_" + std::to_string(nbr) + ".map";
		Tools::putFile(FILEPATH "media/conf/game.conf", std::to_string(nbr));
	}
	std::pair<irr::video::IVideoDriver*, irr::scene::ISceneManager*>
	        win_info (_driver, _sceneManager);
	std::map<int, int> colors = config.getColors();
	for (std::map<int, int>::iterator it = colors.begin();
	     it != colors.end();it++){
		std::pair <int, int > info_player1 (it->second + 1, it->first);
		Personage *perso1;
		if (config.getPlayerIA()[it->first] == 1){
			perso1 = new IA(win_info, info_player1,
					      &_map, pair<int, float>(_x, _y));
		} else
			perso1 = new Personage(win_info, info_player1, &_map);
		std::cout << it->first << " ";
		perso1->setControler(it->first);
		_Fighter.push_back(perso1);
	}
	std::cout << std::endl;
	for(int x = 0;x < _x;x++)
		for(int y = 0;y < _y;y++){
			float z = 0;
			z = _noise->bruit_coherent2D(x * 10, y * 10);
			if (!(x % 2 && y % 2) && !isACorner(x, y) && z > 0.5){
				Crate *tmp = new Crate(_driver, _sceneManager, &_Selector,
					_path_obj_crate);
					_map[irr::core::vector2di(x, y)] = tmp;
					tmp->getMesh()->setPosition(
						irr::core::vector3df(x, 0, y));
				}
		}
	for(int x = 0;x < _x;x++)
		for(int y = 0;y < _y;y++){
			if (x % 2 && y % 2){
				Wall *tmp = new Wall(_driver, _sceneManager, &_Selector,
						     _path_obj_wall);
				_map[irr::core::vector2di(x, y)] = tmp;
				tmp->getMesh()->setPosition(irr::core::vector3df(x, 0, y));
			}
				
		}
	for(int x = -1;x < _x + 1;x++){
		Wall *tmp;
		tmp = new Wall(_driver, _sceneManager, &_Selector, _path_obj_wall);
		_map[irr::core::vector2di(x, _y)] = tmp;
		tmp->getMesh()->setPosition(irr::core::vector3df(x, 0, _y));
		tmp = new Wall(_driver, _sceneManager, &_Selector, _path_obj_wall);
		_map[irr::core::vector2di(x, -1)] = tmp;
		tmp->getMesh()->setPosition(irr::core::vector3df(x, 0, -1));
	}
	for(int y = 0;y < _y;y++){
		Wall *tmp;
		tmp = new Wall(_driver, _sceneManager, &_Selector, _path_obj_wall);
		_map[irr::core::vector2di(_x, y)] = tmp;
		tmp->getMesh()->setPosition(irr::core::vector3df(_x, 0, y));
		tmp = new Wall(_driver, _sceneManager, &_Selector, _path_obj_wall);
		_map[irr::core::vector2di(-1, y)] = tmp;
		tmp->getMesh()->setPosition(irr::core::vector3df(-1, 0, y));
	}
}

void Game::addLights()
{
	_sceneManager->addLightSceneNode (0, irr::core::vector3df(0,1000,0),
					  irr::video::SColorf(0.4f,0.4f,0.6f,0.0f), 100.0f);
}

void Game::addBonus(IObject *bonus)
{
	int nbr_empty_square = nbrEmptySquare();
	int pos = Tools::getNbrRandom(1, nbr_empty_square);
	int i = 0;

	for (int x = 0;x < _x;x++){
		for (int y = 0;y < _y;y++){
			if (_map[irr::core::vector2di(x, y)] == nullptr){
				i++;
			}
			if (i == pos){
				_map[irr::core::vector2di(x, y)] = bonus;
				bonus->getMesh()->setPosition(irr::core::vector3df(x, 0, y));
				return ;
			}
		}
	}
}

irr::f32 Game::getFrameDeltaTime(irr::u32 *now_time)
{
	const irr::u32 next_time = _device->getTimer()->getTime();
	const irr::f32 frameDeltaTime = (irr::f32)(next_time - *now_time) / 1000.f;
	*now_time = next_time;
	return (frameDeltaTime);
}

void Game::exec()
{
	int verif = 3;
	int i = 0;
	irr::f32 frameDeltaTime;
	irr::u32 now_time = _device->getTimer()->getTime();

	if (_Fighter.empty() == true)
		_NoFighter = true;
	InitButtonReturn();
	while (_device->run()) {
		if (_MenuBack == true) {
			_MenuBack = false;
			_sceneManager->clear();
			_NoFighter = true;
			return;
		}
		if (_MyEvent->IsKeyDown(irr::KEY_KEY_P)){
			_device->getCursorControl()->setVisible(true);
			buttonReturn->setVisible(true);
			buttonContinue->setVisible(true);
			_Pause = true;
		}
		if (_MyEvent->IsKeyDown(irr::KEY_KEY_M)){
			now_time = _device->getTimer()->getTime();
			_Pause = false;
			_device->getCursorControl()->setVisible(false);
			buttonReturn->setVisible(false);
			buttonContinue->setVisible(false);
		}
		if (_Pause == false){
			_driver->beginScene(true, true,
					    irr::video::SColor(100, 100, 100, 100));
			frameDeltaTime = getFrameDeltaTime(&now_time);
			if (_device->isWindowActive()) {
				//if (_Pause == false) {
				refresh(frameDeltaTime);
				for (int i = 0;
				     i < (int) _Fighter.size(); i++)
					_Fighter[i]->handleEvent(
						_MyEvent,
						frameDeltaTime,
						&_Selector);
			}
		}
		else {
			verif = CheckButton();
			if (verif == 0) {
				buttonContinue->remove();
				buttonReturn->remove();
				_sceneManager->clear();
				music->stopAllSounds();
				music->play2D(FILEPATH "media/musics/menu.wav");
				return;
			}
			if (verif == 1) {
				_Pause = false;
				buttonReturn->setVisible(false);
				buttonContinue->setVisible(false);
			}
		}
		_sceneManager->drawAll();
		gui->drawAll();
		_driver->endScene();
		i++;
	}
}

int Game::getNbrBonus()
{
	int nbr_bonus = 0;

	for (std::map <irr::core::vector2di, IObject *>::iterator it=_map.begin();
	     it!=_map.end(); ++it){
		if (it->second)
			if (it->second->can_be_taken())
				nbr_bonus++;
	}
	return (nbr_bonus);
}

void Game::addAllBonus()
{
	int bonus_to_add;

	bonus_to_add = _nbr_bonus - getNbrBonus();
	int i = 0;
	while (bonus_to_add > 0){
		addBonus(new Bonus(_driver, _sceneManager, &_Selector));
		bonus_to_add--;
		i++;
	}
}

int Game::getTimeRand()
{
	int rd = 0;
	static int save[1];
	static int old = 0;
	int x = 0;

	x = rand() % 2 + 0;
	rd = rand() % 3 + 0;
	while (rd == save[x]  || rd == old) {
		rd = rand() % 3 + 0;
		std::this_thread::sleep_for(std::chrono::microseconds(1000));
	}
	old = rd;
	save[x] = rd;
	return (rd);
}

bool Game::explodeObject(const int x, const int y)
{
	int type;

	if (_map[irr::core::vector2di(x, y)]){
		if (_map[irr::core::vector2di(x, y)]->getType() ==
		    IObject::Type::T_BOMB){
			_map[irr::core::vector2di(x, y)]
				->setEffect(IObject::Effect::EXPLODE);
			return (true);
		}
		if (_map[irr::core::vector2di(x, y)]->is_destructible()){
			type = _map[irr::core::vector2di(x, y)]->getType();
			delete (_map[irr::core::vector2di(x, y)]);
			_map[irr::core::vector2di(x, y)] = nullptr;
			if (getTimeRand() == 2) {
				Bonus *bonus = new Bonus(_driver, _sceneManager,
						      &_Selector);
				_map[irr::core::vector2di(x, y)] = bonus;
				bonus->getMesh()->setPosition
					(irr::core::vector3df(x, 0, y));
			}
			if (type == IObject::Type::T_BONUS)
				return (false);
			else
				return (true);
		}
		return (true);
	}
	return (false);
}

irr::scene::IParticleSystemSceneNode* Game::createFire(const int x, const int y)
{
		irr::scene::IParticleSystemSceneNode* _Particle;
		_Particle = _sceneManager->addParticleSystemSceneNode(false);
		
		irr::scene::IParticleEmitter* em = _Particle->createBoxEmitter(
			irr::core::aabbox3d<irr::f32>(0,0,0,0,0,0),
			irr::core::vector3df(0.0001f,0.0004f,0.0001f),
			80,100,
			irr::video::SColor(0,255,255,255),
			irr::video::SColor(0,255,255,255),
			800,2000,0,
			irr::core::dimension2df(0.1f,0.1f),
			irr::core::dimension2df(2.f,2.f));
		
		_Particle->setEmitter(em);
		em->drop();
		
		irr::scene::IParticleAffector* paf =
			_Particle->createFadeOutParticleAffector();
		_Particle->addAffector(paf);
		paf->drop();  
		_Particle->setScale(irr::core::vector3df(0.002, 0.002, 0.001));
		_Particle->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_Particle->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
		_Particle->setMaterialTexture(0, _driver->getTexture(
			FILEPATH "media/fire/fireball.bmp"));
		_Particle->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
		_Particle->setPosition(irr::core::vector3df(x, 0, y));
		return (_Particle);
}


void Game::explodePersonage(const int x, const int y)
{
	irr::core::vector3df pos_bomb;

	for (int i = 0; i < (int)_Fighter.size(); i++) {
		pos_bomb = _Fighter[i]->getAxe();
		pos_bomb.X = roundf(pos_bomb.X);
		pos_bomb.Y = 0;
		pos_bomb.Z = roundf(pos_bomb.Z);
		if (pos_bomb.X == x && pos_bomb.Z == y) {
			Death_Ghosts *death = new Death_Ghosts(
				_driver, _sceneManager,
				_Fighter[i]->getMesh()->getPosition());
			_Ghost.push_back(death);
			_Death_nbr++;
			_Fighter[i]->Death(_Death_nbr);
			_Zombie.push_back(_Fighter[i]);
			_Fighter.erase(_Fighter.begin() + i);
		}
	}
}

void Game::explodeBomb(const int x, const int y)
{
	int size = 3;
	int i = 1;
	bool count = true;

	i = 1;
	count = true;
	if (_map[irr::core::vector2di(x, y)])
		size = _map[irr::core::vector2di(x, y)]->getPower();
	explodePersonage(x, y);
	while (i < size + 1 && count){
		if (_map[irr::core::vector2di(x, y + i)]){
			if (_map[irr::core::vector2di(x, y + i)]->is_destructible())
				_map[irr::core::vector2di(x, y)]
					->addObject(createFire(x, y + i));
		} else
			_map[irr::core::vector2di(x, y)]
				->addObject(createFire(x, y + i));
		explodePersonage(x, y + i);
		if (explodeObject(x, y + i)){
			count = false;
		}
		i++;
	}
	i = 1;
	count = true;
	while (i < size + 1 && count){
		explodePersonage(x, y - i);
		if (_map[irr::core::vector2di(x, y - i)]){
			if (_map[irr::core::vector2di(x, y - i)]->is_destructible())
				_map[irr::core::vector2di(x, y)]
					->addObject(createFire(x, y - i));
		}  else
			_map[irr::core::vector2di(x, y)]
				->addObject(createFire(x, y - i));
		if (explodeObject(x, y - i))
			count = false;
		i++;
	}
	i = 1;
	count = true;
	while (i < size + 1 && count){
		explodePersonage(x + i, y);
		if (_map[irr::core::vector2di(x + i, y)]){
			if (_map[irr::core::vector2di(x + i, y)]->is_destructible())
				_map[irr::core::vector2di(x, y)]
					->addObject(createFire(x + i, y));
		}  else
			_map[irr::core::vector2di(x, y)]
				->addObject(createFire(x + i, y));
		if (explodeObject(x + i, y))
			count = false;
		i++;
	}
	i = 1;
	count = true;
	while (i < size + 1 && count){
		explodePersonage(x - i, y);
		if (_map[irr::core::vector2di(x - i, y)]){
			if (_map[irr::core::vector2di(x - i, y)]->is_destructible())
				_map[irr::core::vector2di(x, y)]
					->addObject(createFire(x - i, y));
		}  else
			_map[irr::core::vector2di(x, y)]
				->addObject(createFire(x - i, y));
		if (explodeObject(x - i, y))
			count = false;
		i++;
	}
}

void Game::refresh_ghost ()
{
	for (int i = 0; i < (int)_Ghost.size(); i++) {
		_Ghost[i]->getMesh()->setPosition(
			irr::core::vector3df(
				_Ghost[i]->getMesh()->getPosition().X,
				_Ghost[i]->getMesh()->getPosition().Y + 0.01,
				_Ghost[i]->getMesh()->getPosition().Z));
		if (_Ghost[i]->getMesh()->getPosition().Y > 2) {
			_Ghost[i]->run_out();
			_Ghost.erase(_Ghost.begin() + i);
		}
	}
}

irr::scene::ISceneNode* Game::ShowShip()
{
	irr::scene::ISceneNode *mesh = _sceneManager->addAnimatedMeshSceneNode(
		_sceneManager->getMesh(FILEPATH "media/Ship/UFO.obj"), 0,
		isDESTRUCTIBLEandPASSE);
	mesh->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
	mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	mesh->setPosition(irr::core::vector3df(_x / 2, 7,  _y / 2));
	mesh->setScale(irr::core::vector3df(0.055, 0.055, 0.055));
	irr::scene::ISceneNodeAnimator* anim =
		_sceneManager->createRotationAnimator(
			irr::core::vector3df(0, -0.3f,0));
	mesh->addAnimator(anim);
	return (mesh);
}

void Game::ZombiClap()
{
	for (size_t i = 0; i < _Zombie.size(); i++) {
		_Zombie[i]->getMesh()->setFrameLoop(96, 121);
		_Zombie[i]->getMesh()->setAnimationSpeed(70);
	}
}

void Game::DisplayWinner()
{
	irr::scene::ISceneNode *mesh = _sceneManager->addAnimatedMeshSceneNode(
		_sceneManager->
			getMesh(FILEPATH "media/Winner/winner_wall.obj"));
	mesh->setScale(irr::core::vector3df(1, 1, 1));
	mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	mesh->setPosition(irr::core::vector3df(_x /2, 2, _y / 2));
	irr::scene::ISceneNodeAnimator* anim =
		_sceneManager->createRotationAnimator(
			irr::core::vector3df(0, .1f,0));
	mesh->addAnimator(anim);
	anim->drop();
}

int Game::EndScene()
{
	_Light->createLightFloor();
	_Light->DivineRemoveAnimation();
	_Fighter[0]->setRota(irr::core::vector3df(0, 90, 0));
	_Fighter[0]->setFramLoop(66, 86);
	DisplayWinner();
	ZombiClap();
	music->stopAllSounds();
	music->play2D(FILEPATH "media/musics/menu.wav");
	return (1);
}

void Game::isEnd()
{
	static int var = 0;
	static float stop = 0;
	irr::core::vector3df place;
	irr::core::vector3df rt;

	if (_Fighter.size() == 1){
		if (_Count_timer < 1.3)
		{
			place = _Fighter[0]->getAxe();
			rt  = _Fighter[0]->getRotation();
			_Fighter[0]->setPos(
				irr::core::vector3df(_x / 2, place.Y + 0.01,
						     _y / 2),
				irr::core::vector3df(0, rt.Y + 1, 0));
			if (var == 0) {
				_Light->createLightFloor();
				var = 1;
			}
			if (_Claps == false) {
				_Light->createJetFire(_Fighter[0]->getMesh());
				_Light->createDivine(_Fighter[0]->getMesh());
				ShowShip();
				_Claps = true;
			}
		}
		else{
			if (stop == 0) {
				stop = EndScene();
			}
			_Count_end += 0.01;
			if (_Count_end > 2.5) {
				_MenuBack = true;
				var = 0;
				stop = 0;
			}
		}
		_Count_timer += 0.003;
	}
}

void Game::refresh(irr::f32 frameDeltaTime)
{
	static double move = 0.0;

	if (_Solo == true)
		_Cam->SetCamPosition(
			_Fighter[0]->getCamTarget(), _Fighter[0]->getCamAxe(),
			_Fighter[0]->getRotation());
	for (std::map <irr::core::vector2di, IObject *>::iterator
		     it =_map.begin(); it!=_map.end(); ++it){
		if (it->second){
			if (it->second->getEffect() == IObject::Effect::EXPLODE){
				explodeBomb(it->first.X, it->first.Y);
			}
			if (it->second->getMesh()->getID() == ObjectType::isDESTROYED){
				delete (it->second);
				it->second = nullptr;
			}
			if (it->second)
				it->second->frame(frameDeltaTime, &_Selector);
		}
	}
	_skybox->frame(frameDeltaTime, &_Selector);
	move += 5;
	refresh_ghost();
	if (_MyEvent->IsKeyDown(irr::KEY_KEY_V)){
		if (!_upload)
			saveMap(_file_saving_name);
	}
	if (_NoFighter == false)
		isEnd();
}

int Game::nbrEmptySquare()
{
	int nbr_empty_square = 0;

	for (int x = 0;x < _x;x++){
		for (int y = 0;y < _y;y++){
			if (_map[irr::core::vector2di(x, y)] == nullptr){
				nbr_empty_square++;
			}
		}
	}
	return (nbr_empty_square);
}

bool Game::saveMap(const std::string &filename)
{
	std::ofstream filesave(filename.c_str(), std::ios::out | std::ios::trunc);

	filesave << "size\n";
	filesave << _x << "x" << _y << "\n";
	filesave << "gamers\n";

	for (std::vector<Personage*>::iterator it = _Fighter.begin();
		it!=_Fighter.end();it++)
	{
		filesave << "gamer\n";
		filesave << "pos_X:" << (*it)->getAxe().X << "\n";
		filesave << "pos_Y:" << (*it)->getAxe().Y << "\n";
		filesave << "pos_Z:" << (*it)->getAxe().Z << "\n";
		filesave << "rot_X:" << (*it)->getRotation().X << "\n";
		filesave << "rot_Y:" << (*it)->getRotation().Y << "\n";
		filesave << "rot_Z:" << (*it)->getRotation().Z << "\n";
		filesave << "info_one:" << (*it)->getInfoOne() << "\n";
		filesave << "info_two:" << (*it)->getInfoTwo() << "\n";

		filesave << "bomb_number:" << (*it)->getBombNomber() << "\n";
		filesave << "wall_pass:" << (*it)->getWallPass() << "\n";
		filesave << "control:" << (*it)->getControl() << "\n";
		filesave << "fire_up:" << (*it)->getFireUp() << "\n";
		filesave << "put_bomb:" << (*it)->getPutBomb() << "\n";
		filesave << "is_moving:" << (*it)->getIsMoving() << "\n";
		filesave << "speed:" << (*it)->getSpeed() << "\n";
		filesave << "speedmv:" << (*it)->getSpeedMv() << "\n";

		filesave << "endgamer\n";
	}
	filesave << "objects\n";
	for (std::map <irr::core::vector2di, IObject *>::iterator it=_map.begin();
	     it!=_map.end(); ++it){
		if (it->second){
			filesave << it->second->getType() << ":"
				 << it->first.X << ":" << it->first.Y << ":"
				 << it->second->getEffect() << ":" <<
				it->second->getPower() << ":" <<
				it->second->getPathObj() << ":" <<
				"\n";
		}
	}
	return (true);
}

bool Game::loadMap(const std::string &filename)
{
	std::ifstream file(filename.c_str(), std::ios::in);
	std::string type;
	std::string line;
	std::vector <std::string> data;
	std::map <std::string, std::string> data_perso;

        while (getline(file, line)){
		if (line == "size" || line == "gamers" || line == "objects"){
			type = line;
		} else {
			if (type == "size"){
				data = Tools::explode(line, "x");
				std::cout << data[0] << " and " <<
					  data[1] << std::endl;
			}
			if (type == "gamers"){
				if (line == "gamer"){
					data_perso.clear();
				}
				else if (line == "endgamer"){
					std::pair<irr::video::IVideoDriver*, irr::scene::ISceneManager*>
						win_info (_driver, _sceneManager);
					std::pair <int, int > info_player1 (stoi(data_perso["info_one"]), stoi(data_perso["info_two"]));
					Personage *perso1 = new Personage(win_info, info_player1, &_map);
					perso1->setControler(stoi(data_perso["control"]));
					irr::core::vector3df pos(stof(data_perso["pos_X"]), stof(data_perso["pos_Y"]), stof(data_perso["pos_Z"]));
					irr::core::vector3df rot(stof(data_perso["rot_X"]), stof(data_perso["rot_Y"]), stof(data_perso["rot_Z"]));
					perso1->setPos(pos, rot);
					perso1->setBombNomber(stoi(data_perso["bomb_number"]));
					perso1->setWallPass(stoi(data_perso["wall_pass"]));
					perso1->setFireUp(stoi(data_perso["fire_up"]));
					perso1->setPutBomb(stoi(data_perso["put_bomb"]));
					perso1->setIsMoving(stoi(data_perso["is_moving"]));
					perso1->setSpeed(stoi(data_perso["speed"]));
					perso1->setSpeedMv(stoi(data_perso["speedmv"]));
					_Fighter.push_back(perso1);
					for (std::map <std::string, std::string>::iterator it = data_perso.begin();it != data_perso.end();it++){
						std::cout << it->first << " " << it->second << std::endl;
					}
				}
				else {
					data = Tools::explode(line, ":");
					data_perso[data[0]] = data[1];
				}
			}
			if (type == "objects"){
				data = Tools::explode(line, ":");
				IObject *tmp;
				if (stoi(data[0]) == IObject::Type::T_CRATE)
					tmp = new Crate(_driver, _sceneManager, &_Selector,
							data[5]);
				if (stoi(data[0]) == IObject::Type::T_WALL)
					tmp = new Wall(_driver, _sceneManager, &_Selector,
						data[5]);
				if (stoi(data[0]) == IObject::Type::T_BONUS)
					tmp = new Bonus(_driver, _sceneManager, &_Selector, stoi(data[3]));
				if (stoi(data[0]) == IObject::Type::T_BOMB)
					tmp = new Bomb(_driver, _sceneManager, &_Selector, stoi(data[4]));
				addObject(stoi(data[1]), stoi(data[2]), tmp);
			}
		}
        }
	return (true);
}

void Game::addObject(int x, int y, IObject *object)
{
	_map[irr::core::vector2di(x, y)] = object;
	object->getMesh()->setPosition(irr::core::vector3df(x, 0, y));
}

bool Game::isACorner(const int x, const int y) const
{
	if (x == 0)
		if (y < 3 || y > _y - 4)
			return (true);
	if (y == 0)
		if (x < 3 || x > _x - 4)
			return (true);
	if (x == _x - 1)
		if (y < 3 || y > _y - 4)
			return (true);
	if (y == _y - 1)
		if (x < 3 || x > _x - 4)
			return (true);
	return (false);
}
