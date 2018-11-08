/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "Menu.hpp"

void	EventGame(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, Config &configuration)
{
	music->stopAllSounds();
	Game game(device, driver, configuration);
	game.exec();

}
