/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "EventPlayer.hpp"

bool Player::CheckColor()
{
	int i = 0;
	int compt_verif = 0;
	for (auto it = player_color.begin(); it != player_color.end(); it++)
	{
		for (auto save = player_color.begin(); save != player_color.end(); save++) {
			if ((ButtonDelAdd.at(i + 4)->isVisible()) == true) {
				if (it->second == save->second) {
					cout << "============================"
						<< endl;
					compt_verif += 1;
				}
			}
			i++;
		}
		i = 0;
		if (compt_verif >= 2) {
			cout << "FALSE" << endl;
			return false;
		}
		compt_verif = 0;
	}
	cout << "VRAIIIII" << endl;
	return (true);
}

void Player::ChangeButtonColor(irr::video::IVideoDriver *driver, float x, float y, const wchar_t *string)
{
	irr::gui::IGUIButton *new_button;
	new_button = gui_player->addButton(
		irr::core::rect<irr::s32>(x, y, x + 40, y + 50), 0, -1, string);
	new_button->setImage(driver->getTexture(FILEPATH "media/Menu/picture/button.png"));
	Buttonfleche.push_back(new_button);
}

void Player::InitChangeButtonColor(irr::video::IVideoDriver *driver)
{
	ChangeButtonColor(driver, 50, 300, L"<-");
	ChangeButtonColor(driver, 240, 300, L"->");
	ChangeButtonColor(driver, 290, 300, L"<-");
	ChangeButtonColor(driver, 455, 300, L"->");
	ChangeButtonColor(driver, 505, 300, L"<-");
	ChangeButtonColor(driver, 685, 300, L"->");
	ChangeButtonColor(driver, 735, 300, L"<-");
	ChangeButtonColor(driver, 925, 300, L"->");
	for (auto it = Buttonfleche.begin(); it != Buttonfleche.end(); it++)
		(*it)->setVisible(false);
}