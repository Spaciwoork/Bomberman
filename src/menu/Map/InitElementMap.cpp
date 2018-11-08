/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "EventMap.hpp"

void	Map::CreateCube(irr::video::IVideoDriver *driver)
{
	listPathCube.push_back(FILEPATH "media/B_burger.png");
	listPathCube.push_back(FILEPATH "media/B_chest.png");
	listPathCube.push_back(FILEPATH "media/B_companion_cube.png");
	listPathCube.push_back(FILEPATH "media/B_Mario_bonus.png");
	listPathCube.push_back(FILEPATH "media/B_pokeball.png");
	listPathCube.push_back(FILEPATH "media/B_wood_menu.png");

	listPathWall.push_back(FILEPATH "media/W_cube.png");
	listPathWall.push_back(FILEPATH "media/W_grass_pokemon.png");
	listPathWall.push_back(FILEPATH "media/W_Mario_wall.png");
	listPathWall.push_back(FILEPATH "media/W_sponge_menu.png");
	listPathWall.push_back(FILEPATH "media/W_wall_menu.png");
	listPathWall.push_back(FILEPATH "media/W_minecraft_dirt.png");

	for (auto it = listPathWall.begin(); it != listPathWall.end(); it++) {
		catalogWall.push_back(driver->getTexture(it->c_str()));
	}
	for (auto it = listPathCube.begin(); it != listPathCube.end(); it++) {
		catalogBox.push_back(driver->getTexture(it->c_str()));
	}

	posCube.push_back(0.7);
	posCube.push_back(-3.2);
}

void 	Map::InitButtonvalidate(irr::video::IVideoDriver *driver)
{
	buttonValidate = guiMap->addButton(
		irr::core::rect<irr::s32>(350, 75, 650, 175), 0, -1,
		L"VALIDATE");
	buttonValidate->setImage(driver->getTexture(FILEPATH "media/Menu/picture/button.png"));
}

void	Map::CreateChangeButtonFleche(irr::video::IVideoDriver *driver,
	float x, float y, const wchar_t *string)
{
	irr::gui::IGUIButton *new_button;
	new_button = guiMap->addButton(
		irr::core::rect<irr::s32>(x, y, x + 40, y + 50), 0, -1,
		string);
	new_button->setImage(driver->getTexture(FILEPATH "media/Menu/picture/button.png"));
	Buttonfleche.push_back(new_button);
}

void 	Map::InitChangeButtonFleche(irr::video::IVideoDriver *driver)
{
	CreateChangeButtonFleche(driver, 40, 400, L"<-");
	CreateChangeButtonFleche(driver, 320, 400, L"->");
	CreateChangeButtonFleche(driver, 420, 400, L"<-");
	CreateChangeButtonFleche(driver, 680, 400, L"->");
}

void 	Map::InitMenuMap(irr::IrrlichtDevice *device,
	irr::video::IVideoDriver *driver)
{
	backgroundMap = driver->getTexture(FILEPATH "media/Menu/picture/Bomber.jpg");
	guiMap = device->getGUIEnvironment();
	sceneManagerMap = device->getSceneManager();
	irr::scene::ICameraSceneNode *cam = sceneManagerMap->addCameraSceneNode();
	CreateCube(driver);
	InitButtonvalidate(driver);
	InitChangeButtonFleche(driver);
	(void)cam;
}
