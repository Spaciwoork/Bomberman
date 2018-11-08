/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "Menu.hpp"

/// refresh the window

void	Menu::Refresh()
{
	driver->draw2DImage(background_menu, irr::core::position2d<irr::s32>(0,0),
		irr::core::rect<irr::s32>(0,0,1000,800), 0,
		irr::video::SColor(255, 255, 255, 255), true);
	gui->drawAll();
	driver->endScene();

}

/// Send in different part of the construction and display Menu
/// \return 1 if error encountred and 0 if not

int Menu::LoopMenu()
{
	Config configuration;

	while (device->run()) {
		driver->beginScene(true, true,
			irr::video::SColor(107, 111, 111, 172));
		CheckButtonPressed(configuration);
		Refresh();
	}
	device->drop();
	return (0);
}
