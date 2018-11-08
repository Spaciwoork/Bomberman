/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "EventPlayer.hpp"

void	Player::Adder(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, int nbr)
{
	(void)(device);
	(void)(driver);
	ButtonDelAdd.at(nbr)->setVisible(false);
	NamePlayers.at(nbr)->setVisible(true);
	ButtonDelAdd.at(nbr + 4)->setVisible(true);
}

void	Player::Deler(irr::IrrlichtDevice *device,
	irr::video::IVideoDriver *driver, int nbr)
{
	(void)(device);
	(void)(driver);
	ButtonDelAdd.at(nbr)->setVisible(false);
	ButtonDelAdd.at(nbr - 4)->setVisible(true);
	NamePlayers.at(nbr - 4)->setVisible(false);

}

void	Player::AddPlayer(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
{
	int i = 0;
	for (auto it = ButtonDelAdd.begin(); it != ButtonDelAdd.end(); it++)
	{
		if ((*it)->isPressed())
		{
			if ((i == FIRST) || (i == SECOND) || (i == THIRD) || (i == FOURTH)) {
				Adder(device, driver, i);
				return;
			}
			else if ((i == FIFTH) || (i == SIXTH) || (i == SEVENTH) || (i == EIGHTH)) {
				Deler(device, driver, i);
				return;
			}

		}
		i++;
	}
}

void	Player::DisplayPlayer()
{
	if (ButtonDelAdd.at(4)->isVisible()) {

		irr::core::vector3df rt;
		rt.Y = rt.Y + 120;
		listBomber.at(0)->setRotation(rt);
		listBomber.at(0)->setVisible(true);
		Buttonfleche.at(0)->setVisible(true);
		Buttonfleche.at(1)->setVisible(true);
	} else {
		listBomber.at(0)->setVisible(false);
		Buttonfleche.at(0)->setVisible(false);
		Buttonfleche.at(1)->setVisible(false);
	}
	if (ButtonDelAdd.at(5)->isVisible()) {
		irr::core::vector3df rt;
		rt.Y = rt.Y + 180;
		listBomber.at(1)->setRotation(rt);
		listBomber.at(1)->setVisible(true);
		Buttonfleche.at(2)->setVisible(true);
		Buttonfleche.at(3)->setVisible(true);

	}else {
		listBomber.at(1)->setVisible(false);
		Buttonfleche.at(2)->setVisible(false);
		Buttonfleche.at(3)->setVisible(false);
	}
	if (ButtonDelAdd.at(6)->isVisible()) {
		irr::core::vector3df rt;
		rt.Y = rt.Y + 180;
		listBomber.at(2)->setRotation(rt);
		listBomber.at(2)->setVisible(true);
		Buttonfleche.at(4)->setVisible(true);
		Buttonfleche.at(5)->setVisible(true);
	}
	else {
		listBomber.at(2)->setVisible(false);
		Buttonfleche.at(4)->setVisible(false);
		Buttonfleche.at(5)->setVisible(false);
	}
	if (ButtonDelAdd.at(7)->isVisible()) {
		irr::core::vector3df rt;
		rt.Y = rt.Y + 240;
		listBomber.at(3)->setRotation(rt);
		listBomber.at(3)->setVisible(true);
		Buttonfleche.at(6)->setVisible(true);
		Buttonfleche.at(7)->setVisible(true);
	}else {
		listBomber.at(3)->setVisible(false);
		Buttonfleche.at(6)->setVisible(false);
		Buttonfleche.at(7)->setVisible(false);
	}

}


void	Player::LoopPlayer(irr::IrrlichtDevice *device,
	irr::video::IVideoDriver *driver)
{
	bool verif;
	while (device->run()) {
		driver->draw2DImage(backgroundPlayer,
			irr::core::position2d<irr::s32>(0, 0),
			irr::core::rect<irr::s32>(0, 0, 1000, 800), 0,
			irr::video::SColor(255, 255, 255, 255), true);
		gui_player->drawAll();
		AddPlayer(device, driver);
		DisplayPlayer();
		sceneManagerPlayer->drawAll();
		CheckClickArrow(driver);
		if (buttonValidate->isPressed()) {
			verif = CheckColor();
			if (verif == true)
				return;
		}
		driver->endScene();
	}
}