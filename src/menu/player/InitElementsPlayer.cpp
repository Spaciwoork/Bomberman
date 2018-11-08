/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/
#include "EventPlayer.hpp"

void	Player::InitEditBox(int x, int y, const wchar_t *string)
{
	NamePlayers.push_back(gui_player->addEditBox(string,
		irr::core::rect<irr::s32>(x, y, x + 150, y + 50)));
	NamePlayers.at(compt_box)->setVisible(false);
	compt_box++;
}

void	Player::InitStandardButton(irr::gui::IGUIButton *new_button, const wchar_t *string,
	int x, int y, irr::video::IVideoDriver *driver)
{
	new_button = gui_player->addButton(
		irr::core::rect<irr::s32>(x, y, x + 100, y + 75), 0, -1,
		string);
	new_button->setImage(driver->getTexture(FILEPATH "media/Menu/picture/button.png"));
	ButtonDelAdd.push_back(new_button);
}

void	Player::InitButtonDelete(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
{
	(void)(device);
	InitStandardButton(buttonDelete, L"-", 125, 600, driver);
	InitStandardButton(buttonDeletesecond, L"-", 350, 600, driver);
	InitStandardButton(buttonDeletethird, L"-", 575, 600, driver);
	InitStandardButton(buttonDeletefourth, L"-", 800, 600, driver);
	ButtonDelAdd.at(4)->setVisible(false);
	ButtonDelAdd.at(5)->setVisible(false);
	ButtonDelAdd.at(6)->setVisible(false);
	ButtonDelAdd.at(7)->setVisible(false);
}

irr::scene::IAnimatedMeshSceneNode *Player::CreatePlayer(irr::video::IVideoDriver *driver, irr::io::path &filename, float x, float y)
{
	irr::scene::IAnimatedMeshSceneNode *Bomber;
	Bomber = sceneManagerPlayer->addAnimatedMeshSceneNode(
		sceneManagerPlayer->getMesh(FILEPATH "media/Menu/picture/Bomberman.obj"));
	Bomber->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	material.setTexture(0, driver->getTexture(filename));
	material.Lighting = false;
	material.NormalizeNormals = true;
	cout << "step init materialize" << endl;
	Bomber->getMaterial(0) = material;
	Bomber->setScale(irr::core::vector3df(0.05, 0.06, 0.05));
	Bomber->setPosition(irr::core::vector3df(x, y, 6));
	Bomber->setVisible(false);
	return (Bomber);
}

void	Player::InitCreatePlayer(irr::video::IVideoDriver *driver)
{
	irr::scene::IAnimatedMeshSceneNode *Bomber;
	listPath.push_back(FILEPATH "media/Menu/picture/red_body.png");
	listPath.push_back(FILEPATH "media/Menu/picture/blue_body.png");
	listPath.push_back(FILEPATH "media/Menu/picture/black_body.png");
	listPath.push_back(FILEPATH "media/Menu/picture/gold_body.png");
	pos_player.push_back(-3.6);
	Bomber = CreatePlayer(driver, listPath.at(0), pos_player.at(0), -0.7);
	listBomber.push_back(Bomber);
	player_color[0] = 0;
	pos_player.emplace_back(-1.2);
	Bomber = CreatePlayer(driver, listPath.at(1), pos_player.at(1), -0.7);
	listBomber.push_back(Bomber);
	player_color[1] = 1;
	pos_player.emplace_back(1.2);
	Bomber = CreatePlayer(driver, listPath.at(2), pos_player.at(2), -0.7);
	listBomber.push_back(Bomber);
	player_color[2] = 2;
	pos_player.emplace_back(3.8);
	Bomber = CreatePlayer(driver, listPath.at(3), pos_player.at(3), -0.7);
	listBomber.push_back(Bomber);
	player_color[3] = 3;
}

void 	Player::InitButtonvalidate(irr::video::IVideoDriver *driver)
{
	buttonValidate = gui_player->addButton(
		irr::core::rect<irr::s32>(350, 75, 650, 175), 0, -1,
		L"VALIDATE");
	buttonValidate->setImage(driver->getTexture(FILEPATH "media/Menu/picture/button.png"));
}

void	Player::CreateButtonIA(const wchar_t *string, float x, float y, irr::video::IVideoDriver *driver)
{
	irr::gui::IGUIButton *new_button;
	new_button = gui_player->addButton(
		irr::core::rect<irr::s32>(x, y, x + 100, y + 75), 0, -1,
		string);
	new_button->setImage(driver->getTexture(FILEPATH "media/Menu/picture/button.png"));
	new_button->setPressedImage(driver->getTexture(FILEPATH "media/Menu/picture/blue_button.png"));
	new_button->setIsPushButton(true);
	ButtonIA.push_back(new_button);
}

void	Player::InitButtonIA(irr::video::IVideoDriver *driver)
{
	CreateButtonIA(L"IA", 125, 700, driver);
	CreateButtonIA(L"IA", 350, 700, driver);
	CreateButtonIA(L"IA", 575, 700, driver);
	CreateButtonIA(L"IA", 800, 700, driver);
}

void	Player::InitComponentPlayer(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
{
	backgroundPlayer = driver->getTexture(
		FILEPATH "media/player.jpg");
	gui_player = device->getGUIEnvironment();
	InitStandardButton(buttonAdd, L"+", 125, 600, driver);
	InitStandardButton(buttonAddsecond, L"+", 350, 600, driver);
	InitStandardButton(buttonAddthird, L"+", 575, 600, driver);
	InitStandardButton(buttonAddfourth, L"+", 800, 600, driver);
	compt_box = 0;
	InitEditBox(100, 500, L"PLAYER 1");
	InitEditBox(325, 500, L"PLAYER 2");
	InitEditBox(550, 500, L"PLAYER 3");
	InitEditBox(775, 500, L"PLAYER 4");
	InitButtonDelete(device, driver);
	sceneManagerPlayer = device->getSceneManager();
	irr::scene::ICameraSceneNode *cam = sceneManagerPlayer->addCameraSceneNode();
	InitCreatePlayer(driver);
	InitChangeButtonColor(driver);
	InitButtonvalidate(driver);
	InitButtonIA(driver);
	(void)(cam);
}
