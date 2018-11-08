/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "Menu.hpp"
#include "Game.hpp"

irr::gui::IGUIButton *Game::InitButton(const wchar_t *string, int x, int y)
{
	irr::gui::IGUIButton *button;
	button = gui->addButton(irr::core::rect<irr::s32>(x, y, x + 200, y + 100), 0, -1,
		string);
	button->setImage(_driver->getTexture(FILEPATH "media/Menu/picture/button.png"));
	button->setPressedImage(_driver->getTexture(FILEPATH "media/Menu/picture/orange.png"));
	return (button);
}

void	Game::InitButtonReturn()
{
	gui = _device->getGUIEnvironment();
	gui->getSkin()->setFont(gui->getFont(FILEPATH "media/Menu/picture/bigfont.png"),
		irr::gui::EGDF_BUTTON);
	buttonContinue = InitButton(L"CONTINUE", 250, 600);
	buttonReturn = InitButton(L"MENU", 500, 600);
	buttonReturn->setVisible(false);
	buttonContinue->setVisible(false);
}

int	Game::CheckButton()
{
	if (buttonReturn->isPressed())
		return (0);
	if (buttonContinue->isPressed())
		return (1);
	return (2);
}
