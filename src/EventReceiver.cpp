/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** Created by MP,
*/

#include "EventReceiver.hpp"

EventReceiver::EventReceiver()
{
	for (int key = 0; key < irr :: KEY_KEY_CODES_COUNT; key++)
		_Key_IsDown[key] = false;
	_IsRun = false;
}

EventReceiver::~EventReceiver()
{
}

bool EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return _Key_IsDown[keyCode];
}

irr :: EKEY_CODE EventReceiver::Get_Key_Pressed(void) const
{
	for (int key = 0; key < irr::KEY_KEY_CODES_COUNT; key++)
		if (IsKeyDown((irr::EKEY_CODE)(key)))
			return ((irr :: EKEY_CODE)(key));
	return ((irr :: EKEY_CODE)(0));
}

bool EventReceiver::getIsRun()
{
	return (_IsRun);
}

bool	EventReceiver::OnEvent(const irr :: SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		_Key_IsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		_IsRun = true;
		return (true);
	}
	_IsRun = false;
	return (false);
}
