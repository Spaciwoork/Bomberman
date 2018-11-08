/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#ifndef CPP_INDIE_STUDIO_EVENTSAVE_HPP
#define CPP_INDIE_STUDIO_EVENTSAVE_HPP

#if WIN32
	#include <Windows.h>
#else
	#include <stdio.h>
	#include <wchar.h>
	#include <dirent.h>
#endif
#include "Menu.hpp"

class Save
{
	private:
	irr::video::ITexture *background_menu;
	vector<wchar_t *> list_files;
	irr::gui::IGUIEnvironment *gui_save;
	irr::gui::IGUIStaticText *texte;
	irr::gui::IGUIComboBox *box;
	irr::IrrlichtDevice *save_device;
	vector<irr::gui::IGUIButton *> ButtonSave;
	irr::gui::IGUIButton *buttonReturn;
	irr::gui::IGUIButton *buttonValidate;
	vector<irr::gui::IGUIButton *> ButtonSelect;
	const wchar_t *file_selected;
	public:
	void	InitContentSave();
	void	LoopSave(irr::IrrlichtDevice *, irr::video::IVideoDriver *);
	void	open_save();
	void	InitContentSave(irr::IrrlichtDevice *, irr::video::IVideoDriver *);
	void	InitMenuDeroulan();
	void 	InitButtonStandard(irr::gui::IGUIButton *, const wchar_t *, int , int, irr::video::IVideoDriver *);
	void	delete_element(Config &config);
};

wchar_t * ambstowcs(char const *sczA);


#endif //CPP_INDIE_STUDIO_EVENTSAVE_HPP
