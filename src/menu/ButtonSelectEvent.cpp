/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "Menu.hpp"
#include "EventPlayer.hpp"
#include "EventMap.hpp"

///send to the different Function of menu or load game
///


void	Menu::CheckButtonPressed(Config &configuration)
{
	int i = 0;
	for (auto it = ButtonSelect.begin(); it != ButtonSelect.end(); it++) {
		if ((*it)->isPressed()) {
			switch (i) {
			case PLAYER:
				for (auto it = ButtonSelect.begin(); it != ButtonSelect.end(); it++)
					(*it)->setVisible(false);
				
				EventPlayer(device, driver, configuration);
				for (auto it = ButtonSelect.begin(); it != ButtonSelect.end(); it++)
					(*it)->setVisible(true);
				break;
			case SAVE:
				for (auto it = ButtonSelect.begin(); it != ButtonSelect.end(); it++)
					(*it)->setVisible(false);
				EventSave(device, driver, configuration);
				for (auto it = ButtonSelect.begin(); it != ButtonSelect.end(); it++)
					(*it)->setVisible(true);
				break;
			case MAP:
				for (auto it = ButtonSelect.begin(); it != ButtonSelect.end(); it++)
					(*it)->setVisible(false);
				EventMap(device, driver, configuration);
				for (auto it = ButtonSelect.begin(); it != ButtonSelect.end(); it++)
					(*it)->setVisible(true);
				break;
			case GAME:
				for (auto it = ButtonSelect.begin(); it != ButtonSelect.end(); it++)
					(*it)->setVisible(false);
				EventGame(device, driver, configuration);
				for (auto it = ButtonSelect.begin(); it != ButtonSelect.end(); it++)
					(*it)->setVisible(true);
				break;
			}
		}
		i++;
	}
}
