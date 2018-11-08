/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "Menu.hpp"

void Menu::InitButtonPlay(irr::gui::IGUIButton *new_button)
{
	new_button = gui->addButton(
		irr::core::rect<irr::s32>(300, 300, 700, 500), 0, -1,
	L"PLAY");
	new_button->setImage(driver->getTexture(FILEPATH "media/Menu/picture/blue_button.png"));
	new_button->setPressedImage(driver->getTexture(FILEPATH "media/Menu/picture/orange.png"));
	ButtonSelect.push_back(new_button);
}

void Menu::InitImage()
{
	irr::core::rect<irr::s32> rectangle;

	background_menu = driver->getTexture(FILEPATH "media/Menu/picture/background_menu.png");
}

void Menu::InitText()
{
	texte = gui->addStaticText(L"NUMBERS OF PLAYERS",
		irr::core::rect<irr::s32>(100, 80, 200, 600), false, false,
		0, -1, false);
}

/// Init a standard button with texture, position, clicker ...
/// \param new_button
/// \param string
/// \param x
/// \param y

void Menu::InitButtonStandard(irr::gui::IGUIButton *new_button, const wchar_t *string, int x, int y)
{
	new_button = gui->addButton(
		irr::core::rect<irr::s32>(x, y, x + 200, y + 100), 0, -1,
		string);
	new_button->setImage(driver->getTexture(FILEPATH "media/Menu/picture/button.png"));
	new_button->setPressedImage(driver->getTexture(FILEPATH "media/Menu/picture/orange.png"));
	ButtonSelect.push_back(new_button);
}
