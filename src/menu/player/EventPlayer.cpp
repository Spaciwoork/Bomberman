/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "EventPlayer.hpp"
#include "Config.hpp"

const wchar_t *Config::getSavePlay() const
{
	return (savePlay);
}

vector<const wchar_t *> Config::getSavePseudo()
{
	return (SavePseudo);
}

void 	Config::SaveIA(vector<irr::gui::IGUIButton *> ButtonIA)
{
	int i = 0;
	for (auto it = ButtonIA.begin(); it != ButtonIA.end(); it++)
	{
		if (ButtonIA.at(i)->isPressed())
			PlayerIA[i] = 1;
		else
			PlayerIA[i] = 0;
		i++;
	}
}

void 	Config::SaveNbrPlayer(vector<irr::gui::IGUIButton *> ButtonDelAdd)
{
	nbrPlayers = 0;
	for (auto it = (ButtonDelAdd.begin() + 4); it != (ButtonDelAdd.end()); it++) {
		if ((*it)->isVisible())
			nbrPlayers++;
	}
	cout << "NBR ==>" << nbrPlayers << endl;
}

void 	Config::SaveColor(map<int, int> ColorPlayer, vector<irr::gui::IGUIButton *> ButtonDelAdd)
{
	cout << "---------" << nbrPlayers << endl;
	if (!SaveColorPlayer.empty())
		SaveColorPlayer.clear();
	int i = 4;
	int pos_save = 0;
	int pos = 0;
	for (auto it = ColorPlayer.begin(); it != ColorPlayer.end(); it++)
	{
		if (ButtonDelAdd.at(i)->isVisible()) {
			SaveColorPlayer[pos] = ColorPlayer[pos_save];
			pos++;
		}
		pos_save++;
		i++;
	}
}

void 	Config::SaveName(vector<irr::gui::IGUIEditBox *> NamePlayers)
{
	const wchar_t *pseudo;
	for (auto it = NamePlayers.begin(); it != NamePlayers.end(); it++)
	{
		if ((*it)->isVisible()) {
			pseudo = ((*it)->getText());
			wcout << pseudo << endl;
			SavePseudo.push_back(pseudo);
		}
	}
}

int Config::getNbrPlayer() const
{
	return (nbrPlayers);
}

map<int, int> Config::getColors()
{
	return (SaveColorPlayer);
}

map<int, int> Config::getPlayerIA()
{
	return (PlayerIA);
}

vector<const wchar_t *> Config::getPseudos()
{
	return (SavePseudo);
}

void 	Player::endPlayerMenu(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, Config &configuration)
{
	(void)driver;
	(void)device;
	configuration.SaveNbrPlayer(ButtonDelAdd);
	configuration.SaveColor(player_color, ButtonDelAdd);
	configuration.SaveName(NamePlayers);
	configuration.SaveIA(ButtonIA);
	for (auto it = Buttonfleche.begin(); it != Buttonfleche.end(); it++) {
		(*it)->remove();
	}
	Buttonfleche.clear();
	for (auto it2 = ButtonDelAdd.begin();
		it2 != ButtonDelAdd.end(); it2++) {
		(*it2)->remove();
	}
	ButtonDelAdd.clear();
	for (auto it3 = listBomber.begin(); it3 != listBomber.end(); it3++) {
		(*it3)->remove();
	}
	listBomber.clear();
	for (auto it4 = NamePlayers.begin(); it4 != NamePlayers.end(); it4++) {
		(*it4)->remove();
	}
	for (auto it5 = ButtonIA.begin(); it5 != ButtonIA.end(); it5++) {
		(*it5)->remove();
	}
	player_color.clear();
	NamePlayers.clear();
	listPath.clear();
	buttonValidate->remove();
	return;
}

void	EventPlayer(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, Config &configuration)
{
	Player players;
	players.InitComponentPlayer(device, driver);
	players.LoopPlayer(device, driver);
	players.endPlayerMenu(device, driver, configuration);
	return;
}
