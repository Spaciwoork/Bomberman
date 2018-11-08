//
// Created by spaciwork on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_EVENTMAP_HPP
#define CPP_INDIE_STUDIO_EVENTMAP_HPP

#include "Menu.hpp"

using namespace std;

class Map {
	private:
	irr::video::ITexture *backgroundMap;
	irr::gui::IGUIEnvironment *guiMap;
	irr::scene::ISceneManager* sceneManagerMap;
	vector<string> listPathCube;
	vector<string> listPathWall;
	vector<double>posCube;
	vector<irr::scene::IAnimatedMeshSceneNode *> listCube;
	vector<irr::gui::IGUIButton *> Buttonfleche;
	irr::gui::IGUIButton *buttonValidate;
	int newNbrPathWall;
	int newNbrPathCube;
	int _count;
	vector<irr::video::ITexture *> catalogWall;
	vector<irr::video::ITexture *> catalogBox;
	public:
	void InitMenuMap(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver);
	void CreateCube(irr::video::IVideoDriver *driver);
	irr::scene::IAnimatedMeshSceneNode *CubeCreator(irr::video::IVideoDriver *driver, irr::io::path &filename, float x, float y);
	irr::video::SMaterial material;
	void 	InitButtonvalidate(irr::video::IVideoDriver *);
	void 	InitChangeButtonFleche(irr::video::IVideoDriver *driver);
	void	CreateChangeButtonFleche(irr::video::IVideoDriver *driver,
	float x, float y, const wchar_t *string);
	void	LoopMap(irr::IrrlichtDevice *device,
		irr::video::IVideoDriver *driver);
	void 	wallRight();
	void 	wallLeft();
	void 	cubeRight();
	void 	cubeLeft();
	void	CheckClickArrow();
	void 	SaveAndDelete(irr::video::IVideoDriver *, Config&);
};

#endif //CPP_INDIE_STUDIO_EVENTMAP_HPP
