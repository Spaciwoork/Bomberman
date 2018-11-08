/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "EventMap.hpp"

void 	Map::cubeLeft()
{
	if ((newNbrPathCube - 1) == -1)
		newNbrPathCube = (int)listPathCube.size() - 1;
	else
		newNbrPathCube -= 1;
}

void 	Map::cubeRight()
{
	if ((newNbrPathCube + 1) == (int)listPathCube.size())
		newNbrPathCube = 0;
	else
		newNbrPathCube += 1;
}

void 	Map::wallLeft()
{
	if ((newNbrPathWall - 1) == -1)
		newNbrPathWall =  (int)listPathWall.size() - 1;
	else
		newNbrPathWall -= 1;
}

void	Map::wallRight()
{
	if ((newNbrPathWall + 1) == (int)listPathWall.size())
		newNbrPathWall = 0;
	else
		newNbrPathWall += 1;
}

void	Map::CheckClickArrow()
{
	int i = 0;
	for (auto it = Buttonfleche.begin(); it != Buttonfleche.end(); it++) {
		if ((*it)->isPressed()) {
			switch (i)
			{
			case (0):
				wallLeft();
				break;
			case (1):
				wallRight();
				break;
			case (2):
				cubeLeft();
				break;
			case (3):
				cubeRight();
				break;
			}
		}
		i++;
	}
}

void	Map::LoopMap(irr::IrrlichtDevice *device,
	irr::video::IVideoDriver *driver)
{
	bool verif;
	newNbrPathWall = 0;
	newNbrPathCube = 0;
	_count = 0;
	while (device->run())
	{
		driver->draw2DImage(backgroundMap, irr::core::position2d<irr::s32>(0, 0),
			irr::core::rect<irr::s32>(0, 0, 1000, 800), 0,
			irr::video::SColor(255, 255, 255, 255), true);
		if (_count % 10 == 0)
			CheckClickArrow();
		driver->draw2DImage(catalogBox.at(newNbrPathCube), irr::core::position2d<irr::s32>(480, 300),
			irr::core::rect<irr::s32>(0, 0, 190, 190), 0,
			irr::video::SColor(255, 255, 255, 255), true);
		driver->draw2DImage(catalogWall.at(newNbrPathWall), irr::core::position2d<irr::s32>(100 ,300),
			irr::core::rect<irr::s32>(0, 0, 190 , 190), 0,
			irr::video::SColor(255, 255, 255, 255), true);
		if (buttonValidate->isPressed())
			return;
		guiMap->drawAll();
		sceneManagerMap->drawAll();
		driver->endScene();
		_count++;
	}
	(void)verif;
}
