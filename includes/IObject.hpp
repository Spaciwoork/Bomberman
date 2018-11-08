//
// EPITECH PROJECT, 2018
// IObject
// File description:
// IObject
//

#ifndef IOBJECT_HPP_
# define IOBJECT_HPP_

#include <irrlicht/irrlicht.h>
#include <vector>
#include "ElementType.hpp"

class IObject
{
public:
	enum Effect
	{
		BOMB_UP,
		SPEED_UP,
		FIRE_UP,
		WALL_PASS,
		NOTHING,
		EXPLODE
	};
public:
	enum Type
	{
		T_NOTHING,
		T_BOMB_UP,
		T_SPEED_UP,
		T_FIRE_UP,
		T_WALL_PASS,
		T_CRATE,
		T_WALL,
		T_BONUS,
		T_BOMB
	};

public:
	IObject(const bool is_destructible, const bool can_be_taken);
	virtual ~IObject();
	bool is_destructible() const;
	bool can_be_taken() const;
	irr::scene::ISceneNode *getMesh();
	virtual Effect getEffect();
	virtual void setEffect(const Effect effect);
	virtual void frame(irr::f32 frameDeltaTime, irr::scene::ITriangleSelector **selector);
	virtual void DropObject();
	int getPower() const;
	int getType() const;
	void addObject(irr::scene::ISceneNode *node);
	std::string getPathObj() const;
private:
	bool _is_destructible;
	bool _can_be_taken;
protected:
	Effect _effect;
	irr::scene::ISceneNode *_mesh;
	std::string _path_obj;
	std::vector<irr::scene::ISceneNode *> _children;
	int _type;
	int _power;
        //irr::scene::IAnimatedMeshSceneNode *_mesh;

};

#endif
