//
// EPITECH PROJECT, 2018
// main
// File description:
// main
//

#include <irrlicht/irrlicht.h>
#include "Game.hpp"
#include "Menu.hpp"


int main(void) {
	Menu menu;

	menu.InitComponentMenu();
	menu.LoopMenu();
	return 0;
}
