/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "EventSave.hpp"

void	Save::LoopSave(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
{
	while (device->run()) {
		driver->draw2DImage(background_menu,
			irr::core::position2d<irr::s32>(0, 0),
			irr::core::rect<irr::s32>(0, 0, 1000, 800), 0,
			irr::video::SColor(255, 255, 255, 255), true);
		gui_save->drawAll();
		if (ButtonSave.at(0)->isPressed()) {
			file_selected = box->getItem(box->getSelected());
			file_selected = wcsdup(box->getItem(box->getSelected()));
			std::wcout << file_selected << std::endl;
			return ;
		}
		driver->endScene();
	}
}
