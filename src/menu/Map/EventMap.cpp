/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "EventMap.hpp"

Config::Config()
{
	PathCube = FILEPATH "media/Menu/picture/box.obj";
	PathWall = FILEPATH "Blocs/wall/wall.obj";
	savePlay = wcsdup((wchar_t *)"?");
}

void	Config::SavePathCube(int Cube, int Wall)
{
	switch (Cube)
	{
	case 0:
		PathCube = FILEPATH "Blocs/box/krabbypatty.obj";
		break;
	case 1:
		PathCube = FILEPATH "Blocs/box/chest.obj";
		break;
	case 2:
		PathCube = FILEPATH "Blocs/box/companion_cube.obj";
		break;
	case 3:
		PathCube = FILEPATH "Blocs/box/mario_bonus.obj";
		break;
	case 4:
		PathCube = FILEPATH "Blocs/box/pokeball.obj";
		break;
	case 5:
		PathCube = FILEPATH "media/Menu/picture/box.obj";
		break;
	}
	switch (Wall)
	{
	case 0:
		PathWall = FILEPATH "Blocs/wall/cube.obj";
		break;
	case 1:
		PathWall = FILEPATH "Blocs/wall/grass_pokemon.obj";
		break;
	case 2:
		PathWall = FILEPATH "Blocs/wall/brick.obj";
		break;
	case 3:
		PathWall = FILEPATH "Blocs/wall/sponge.obj";
		break;
	case 4:
		PathWall = FILEPATH "Blocs/wall/wall.obj";
		break;
	case 5:
		PathWall = FILEPATH "Blocs/wall/minecraft_dirt.obj";
	}
}

string Config::getPathCube() const
{
	return (PathCube);
}

string Config::getPathWall() const
{
	return (PathWall);
}

void 	Map::SaveAndDelete(irr::video::IVideoDriver *, Config &configuration)
{
	configuration.SavePathCube(newNbrPathCube, newNbrPathWall);
	listPathCube.clear();
	listPathWall.clear();
	for (auto it = Buttonfleche.begin(); it != Buttonfleche.end(); it++)
		(*it)->remove();
	buttonValidate->remove();
}

void	EventMap(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, Config &configuration)
{
	(void)configuration;
	Map mapper;
	mapper.InitMenuMap(device, driver);
	mapper.LoopMap(device, driver);
	mapper.SaveAndDelete(driver, configuration);
}
