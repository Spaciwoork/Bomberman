//
// EPITECH PROJECT, 2018
// Game
// File description:
// Game
//

#ifndef GAME_HPP_
# define GAME_HPP_

#include <iostream>
#include <string>
#include <fstream>
#include <irrlicht/irrlicht.h>
#include <vector>
#include <map>
#include <climits>
#include <cstdint>
#include <irrKlang/irrKlang.h>
#include "Tools.hpp"
#include "IObject.hpp"
#include "Crate.hpp"
#include "Bonus.hpp"
#include "Noise.hpp"
#include "Skybox.hpp"
#include "Wall.hpp"
#include "Personage.hpp"
#include "EventReceiver.hpp"
#include "ElementType.hpp"
#include "Camera.hpp"
#include "Config.hpp"
#include "Death_Ghosts.hpp"
#include "Ia.hpp"
#include "Light.hpp"

extern irrklang::ISoundEngine *music;


class Game
{
	public:
	Game(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
	     Config &config);
	void addLights();
	void addObjects(Config &config);
	void addObject(int x, int y, IObject *object);
	void addBonus(IObject *bonus);
	void exec();
	int getNbrBonus();
	void addAllBonus();
	void refresh(irr::f32 frameDeltaTime);
	int nbrEmptySquare();
	irr::f32 getFrameDeltaTime(std::uint32_t *now_time);
	void fill_selector(irr::scene::IAnimatedMeshSceneNode **node);
	bool saveMap(const std::string &filename);
	bool loadMap(const std::string &filename);
	void explodeBomb(const int x, const int y);
	bool isACorner(const int x, const int y) const;
	int getTimeRand();
	void Ghost(irr::core::vector3df pos);
	void refresh_ghost ();
	void isEnd();
	void ZombiClap();
	void heavenParticle();
	irr::scene::ISceneNode* ShowShip();
	void DisplayWinner();
	int EndScene();
	void	InitButtonReturn();
	irr::gui::IGUIButton *InitButton(const wchar_t *string, int x, int y);
	int CheckButton();

	protected:
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_driver;
	irr::scene::ISceneManager *_sceneManager;
	irr::gui::IGUIEnvironment *gui;
	std::string _path_obj_wall;
	std::string _path_obj_crate;
	Camera *_Cam;
	std::string _file_saving_name;
	std::vector <irr::scene::IAnimatedMeshSceneNode *> _crates;
	Noise *_noise;
	int _x;
	int _y;
	int _nbr_bonus;
	bool _Solo;
	EventReceiver *_MyEvent;
	irr::video::SMaterial _Material;
	irr::scene::ITriangleSelector *_Selector;
	std::map <irr::core::vector2di, IObject *> _map;
	Skybox *_skybox;
	irr::scene::ISceneNode *_square;
	bool explodeObject(const int x, const int y);
	void explodePersonage(const int x, const int y);
	irr::scene::IParticleSystemSceneNode* createFire(const int x, const int y);
	irr::scene::ISceneNode* LightParticle(Personage *perso);
	std::vector<Personage*>  _Fighter;
	std::vector<Personage*>  _Zombie;
	std::vector<Death_Ghosts*> _Ghost;
	int _Death_nbr;
	Light *_Light;
	bool _upload;
	bool _NoFighter;
	bool _Pause;
	irrklang::ISound *_musicGame;
	irrklang::ISound *_musicVictory;
	float _Count_end;
	bool _MenuBack;
	irr::gui::IGUIButton *buttonReturn;
	irr::gui::IGUIButton *buttonContinue;
	float _Count_timer;
	bool _Claps;
};

#endif
