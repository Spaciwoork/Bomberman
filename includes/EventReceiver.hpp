/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** Created by MP,
*/

#ifndef MYEVENTRECEIVER_HPP
#define MYEVENTRECEIVER_HPP

#include <irrlicht/irrlicht.h>


class EventReceiver : public irr::IEventReceiver
{
	public:
	EventReceiver();
	~EventReceiver();
	virtual bool		OnEvent(const irr :: SEvent &);
	irr :: EKEY_CODE Get_Key_Pressed(void) const;
	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

	bool getIsRun();

	protected:
	bool		_Key_IsDown[irr :: KEY_KEY_CODES_COUNT];
	bool _IsRun;
};

#endif /* !MYEVENTRECEIVER_HPP */
