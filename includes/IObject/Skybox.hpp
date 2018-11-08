//
// EPITECH PROJECT, 2018
// Crate
// File description:
// Crate
//

#ifndef SKYBOX_HPP_
# define SKYBOX_HPP_

#include <irrlicht/irrlicht.h>
#include "IObject.hpp"

class Skybox : public IObject
{
public:
	Skybox(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager);
	virtual ~Skybox();
	virtual void frame(irr::f32 frameDeltaTime, irr::scene::ITriangleSelector **selector);
private:
	irr::scene::IAnimatedMeshSceneNode *_sky1;
	irr::scene::IAnimatedMeshSceneNode *_sky2;
	irr::scene::IAnimatedMeshSceneNode *_sky3;
	irr::scene::IAnimatedMeshSceneNode *_sky4;
	irr::scene::IAnimatedMeshSceneNode *_sky5;
	irr::scene::IAnimatedMeshSceneNode *_sky6;
};

#endif
