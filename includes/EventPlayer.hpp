//
// Created by spaciwork on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_EVENTPLAYER_HPP
#define CPP_INDIE_STUDIO_EVENTPLAYER_HPP

#include "Menu.hpp"

using namespace std;

class Player {
	public:
	enum{
		FIRST = 0,
		SECOND = 1,
		THIRD = 2,
		FOURTH = 3,
		FIFTH = 4,
		SIXTH = 5,
		SEVENTH = 6,
		EIGHTH = 7,
	};
	void	InitStandardButton(irr::gui::IGUIButton *, const wchar_t *, int
		, int, irr::video::IVideoDriver *);

	void	InitComponentPlayer(irr::IrrlichtDevice *device,
					irr::video::IVideoDriver *driver);

	void	LoopPlayer(irr::IrrlichtDevice *device,
			       irr::video::IVideoDriver *driver);

	void	AddPlayer(irr::IrrlichtDevice *, irr::video::IVideoDriver *);
	void	Adder(irr::IrrlichtDevice *device,
			  irr::video::IVideoDriver *driver, int nbr);

	void	InitButtonDelete(irr::IrrlichtDevice *device,
				     irr::video::IVideoDriver *driver);

	void	Deler(irr::IrrlichtDevice *device,
			  irr::video::IVideoDriver *driver, int nbr);

	void	InitEditBox(int x, int y, const wchar_t *string);
	void	DisplayPlayer();
	irr::scene::IAnimatedMeshSceneNode *CreatePlayer(
		irr::video::IVideoDriver *driver, irr::io::path &,
		float x, float y);

	void	InitCreatePlayer(irr::video::IVideoDriver *driver);
	void	InitChangeButtonColor(irr::video::IVideoDriver *driver);
	void	ChangeButtonColor(irr::video::IVideoDriver *driver, float x,
				      float y, const wchar_t *string);

	void 	CheckClickArrow(irr::video::IVideoDriver *);
	void 	ChangeColorLeft(int nbr, irr::video::IVideoDriver *);
	void 	ChangeColorRight(int nbr, irr::video::IVideoDriver *);
	bool 	CheckColor();
	void 	InitButtonvalidate(irr::video::IVideoDriver *);

	void 	endPlayerMenu(irr::IrrlichtDevice *device,
				  irr::video::IVideoDriver *driver, Config &);
	void 	InitButtonIA(irr::video::IVideoDriver *);
	void	CreateButtonIA(const wchar_t *string,
				   float x, float y,
				   irr::video::IVideoDriver *);

	private:
	int compt_box;
	map<int, double > pos;
	irr::gui::IGUIButton *buttonAdd;
	irr::gui::IGUIButton *buttonAddsecond;
	irr::gui::IGUIButton *buttonAddthird;
	irr::gui::IGUIButton *buttonAddfourth;
	irr::gui::IGUIButton *buttonDelete;
	irr::gui::IGUIButton *buttonDeletesecond;
	irr::gui::IGUIButton *buttonDeletethird;
	irr::gui::IGUIButton *buttonDeletefourth;
	irr::gui::IGUIButton *buttonValidate;
	irr::video::ITexture *backgroundPlayer;
	irr::gui::IGUIEnvironment *gui_player;
	vector<irr::gui::IGUIButton *> ButtonDelAdd;
	vector<irr::gui::IGUIEditBox *> NamePlayers;
	irr::scene::ISceneManager* sceneManagerPlayer;
	vector<irr::scene::IAnimatedMeshSceneNode *> listBomber;
	vector<irr::gui::IGUIButton *> Buttonfleche;
	vector<irr::gui::IGUIButton *> ButtonIA;
	vector<irr::gui::IGUIButton *> ButtonJoystick;
	irr::video::SMaterial material;
	vector<irr::io::path> listPath;
	map<int, int>player_color;
	vector<double>pos_player;
};

#endif //CPP_INDIE_STUDIO_EVENTPLAYER_HPP
