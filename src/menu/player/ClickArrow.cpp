/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "EventPlayer.hpp"


void 	Player::ChangeColorLeft(int nbr, irr::video::IVideoDriver *driver)
{
	cout << "LEFT" << endl;
	if (nbr > 1 )
		nbr = nbr - 1;
	if (nbr == 3)
		nbr = nbr - 1;
	if (nbr >= 5)
		nbr = nbr - 2;
	cout << nbr << endl;
	listBomber.at(nbr)->remove();
	if (player_color[nbr] == 0)
		player_color[nbr] += 3;
	else
		player_color[nbr] -= 1;
	listBomber.at(nbr) = CreatePlayer(driver, listPath.at(player_color[nbr]), pos_player.at(nbr), -0.7);

}

void 	Player::ChangeColorRight(int nbr, irr::video::IVideoDriver *driver)
{
	if (nbr > 0)
		nbr = nbr - 1;
	if (nbr > 1 )
		nbr = nbr - 1;
	if (nbr > 2)
		nbr = nbr - 1;
	if (nbr >= 3)
		nbr = nbr - 1;
	cout << nbr << endl;
	listBomber.at(nbr)->remove();
	if (player_color[nbr] == 3)
		player_color[nbr] = 0;
	else
		player_color[nbr] += 1;
	listBomber.at(nbr) = CreatePlayer(driver, listPath.at(player_color[nbr]), pos_player.at(nbr), -0.7);
}

void	Player::CheckClickArrow(irr::video::IVideoDriver *driver)
{
	int i = 0;
	for (auto it = Buttonfleche.begin(); it != Buttonfleche.end(); it++) {
		if ((*it)->isPressed()) {
			if (i % 2 == 0)
				ChangeColorLeft(i, driver);
			if (i % 2 != 0)
				ChangeColorRight(i, driver);
		}
		i++;
	}
}