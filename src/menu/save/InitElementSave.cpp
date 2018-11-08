/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "EventSave.hpp"

void	 Save::InitButtonStandard(irr::gui::IGUIButton *new_button, const wchar_t *string, int x, int y, irr::video::IVideoDriver *driver)
{
	new_button = gui_save->addButton(
		irr::core::rect<irr::s32>(x, y, x + 400, y + 100), 0, -1,
		string);
	new_button->setImage(driver->getTexture(FILEPATH "media/Menu/picture/button.png"));
	new_button->setPressedImage(driver->getTexture("src/menu/picture/orange.png"));
	ButtonSave.push_back(new_button);
}

void	Save::InitContentSave(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
{
	background_menu = driver->getTexture(FILEPATH "media/bomberSave.jpg");
	//open_save();
	gui_save = device->getGUIEnvironment();
	gui_save->getSkin()->setFont(gui_save->getFont(FILEPATH "media/Menu/picture/button.png"),
		irr::gui::EGDF_BUTTON);
	InitMenuDeroulan();
	InitButtonStandard(buttonValidate, L"VALIDATE", 300, 600, driver);
}

void	Save::InitMenuDeroulan()
{
	box = gui_save->addComboBox(irr::core::rect<irr::s32>(100, 100, 1000, 250));
	auto it = list_files.begin();
	wchar_t message[100];
	while (it != list_files.end()) {
		wcout << *it << endl;
		swprintf(message, 100, *it);
		box->addItem(message);
		it++;
	}
	swprintf(message, 100, L"New game");
	box->addItem(message);
}
