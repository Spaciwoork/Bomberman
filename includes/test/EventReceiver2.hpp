/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** Created by MP,
*/

#ifndef EVENTRECEIVER_HPP
#define EVENTRECEIVER_HPP

#include <irrlicht/irrlicht.h>

class CEventReceiver : public irr::IEventReceiver
{
	public :
	//Le constructeur.
	CEventReceiver(irr::scene::IAnimatedMeshSceneNode* Nmodele);
	//Capte automatiquement les events.
	virtual bool OnEvent(const irr::SEvent &event);
	//Met a jour la position du mesh.
	void majPosMesh();

	private :
	//Le modele qu'on va controler.
	irr::scene::IAnimatedMeshSceneNode* m_Nmodele;
	//Indique si on est deja en mouvement ou pas.
	bool m_isMoving;
};

#endif /* !CPP_EVENTRECEIVER_HPP */


