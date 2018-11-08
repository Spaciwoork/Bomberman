/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include <irrKlang/irrKlang.h>
#include "Menu.hpp"

irrklang::ISoundEngine *music;

Menu::Menu()
{
		device = irr::createDevice(
		irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(1000,800),
		32, false, true, false, 0);
}

void	Menu::Return_menu()
{
	cout << "toto" << endl;
}


irr::core::rect<irr::s32> CreateRectangle(int X_haut, int Y_haut, int X_bas, int Y_bas)
{
	irr::core::position2d<irr::s32> positionHaut;
	irr::core::position2d<irr::s32> positionBas;
	irr::core::rect<irr::s32> rectangle;

	positionHaut.X = X_haut;
	positionHaut.Y = Y_haut;
	positionBas.X = X_bas;
	positionBas.Y = Y_bas;
	rectangle.UpperLeftCorner = positionHaut;
	rectangle.LowerRightCorner = positionBas;
	return (rectangle);
}

/// init component for the Loop Menu : Driver, GUI, Scene ...

void Menu::InitComponentMenu()
{
	driver = device->getVideoDriver();
	sceneManager = device->getSceneManager();
	music = irrklang::createIrrKlangDevice();

	if (driver == nullptr)
		exit(84);
	device->setResizable(false);
	device->setWindowCaption(L"BOMBERMAN");
	sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 0, 0),
					 irr::core::vector3df(5, 0, 0));
	gui = device->getGUIEnvironment();
	gui->getSkin()->setFont(gui->getFont(
		FILEPATH "media/Menu/picture/bigfont.png"),
		irr::gui::EGDF_BUTTON);
	InitButtonStandard(buttonAddPlayer, L"PLAYERS", 100, 600);
	InitButtonStandard(buttonSave, L"SAVE", 400, 600);
	InitButtonStandard(mapSize, L"MAP", 700, 600);
	InitButtonPlay(buttonPlay);
	InitImage();
	music->play2D(FILEPATH "media/musics/menu.wav");
}