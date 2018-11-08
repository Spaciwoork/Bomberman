//
// EPITECH PROJECT, 2018
// IObject
// File description:
// IObject
//

#include "IObject.hpp"

IObject::IObject(const bool is_destructible, const bool can_be_taken)
{
	_is_destructible = is_destructible;
	_can_be_taken = can_be_taken;
	_effect = NOTHING;
	_type = T_NOTHING;
	_power = 0;
}

IObject::~IObject()
{
	_mesh->remove();
	for (std::vector<irr::scene::ISceneNode *>::iterator it = _children.begin();
	     it != _children.end();it++){
		(*it)->remove();
	}
}

bool IObject::is_destructible() const
{
	return (_is_destructible);
}

bool IObject::can_be_taken() const
{
	return (_can_be_taken);
}

irr::scene::ISceneNode *IObject::getMesh()
{
	return (_mesh);
}

IObject::Effect IObject::getEffect()
{
	return (_effect);
}

void IObject::frame(irr::f32 frameDeltaTime, irr::scene::ITriangleSelector **selector)
{
	(void)frameDeltaTime;
	(void)selector;
}

void IObject::DropObject()
{
}

int IObject::getPower() const
{
	return (_power);
}

int IObject::getType() const
{
	return (_type);
}

void IObject::addObject(irr::scene::ISceneNode *node)
{
	_children.push_back(node);
}

void IObject::setEffect(const Effect effect)
{
	_effect = effect;
}

std::string IObject::getPathObj() const
{
	return (_path_obj);
}
