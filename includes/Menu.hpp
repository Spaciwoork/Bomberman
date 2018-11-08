/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#ifndef CPP_INDIE_STUDIO_MENU_HPP
#define CPP_INDIE_STUDIO_MENU_HPP

#include <irrlicht/irrlicht.h>
#include <vector>
#include <map>
#include <iostream>
#include <vector>
#include "Game.hpp"
#include "IObject.hpp"
#include "Crate.hpp"
#include "Noise.hpp"
#include "Config.hpp"

class Menu
{
	public:
	enum{
		PLAYER = 0,
		SAVE = 1,
		MAP = 2,
		GAME = 3,
	};
	Menu();
	void	Return_menu();
	void	InitComponentMenu();
	int	LoopMenu();
	void	Refresh();
	void	InitText();
	void	InitButtonStandard(irr::gui::IGUIButton *,
				       const wchar_t*, int, int);
	void	InitImage();
	void	CheckButtonPressed(Config &config);
	irr::IrrlichtDevice 	*getDevice();
	void	InitButtonPlay(irr::gui::IGUIButton *);

	private:
	irr::IrrlichtDevice *device;
	irr::scene::ISceneManager *sceneManager;
	irr::video::IVideoDriver *driver;
	irr::gui::IGUIEnvironment *gui;
	irr::gui::IGUIFont *font;
	irr::gui::IGUIStaticText *texte;
	irr::gui::IGUIButton *buttonAddPlayer;
	irr::gui::IGUIButton *buttonSave;
	irr::gui::IGUIButton *mapSize;
	irr::gui::IGUIButton *buttonPlay;
	irr::video::ITexture *background_menu;
	irr::core::position2d<irr::s32> position;
	vector<irr::gui::IGUIButton *> ButtonSelect;
};

extern irrklang::ISoundEngine *music;

void	EventSave(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
		      Config &);

void	EventMap(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
		     Config &configuration);

void	EventPlayer(irr::IrrlichtDevice *device,
			irr::video::IVideoDriver *driver, Config &);

void	EventGame(irr::IrrlichtDevice *device,
		      irr::video::IVideoDriver *driver, Config &);

#endif /* !CPP_INDIE_STUDIO_MENU_HPP */
