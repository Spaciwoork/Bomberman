/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#ifndef CPP_INDIE_STUDIO_CONFIG_HPP
#define CPP_INDIE_STUDIO_CONFIG_HPP

using namespace std;

/*Event Map*/

class Config{
	private:
	int nbrPlayers; // nbr of player
	map<int, int>SaveColorPlayer; //number of player and this color 0 red, 1 blue , 2 black , 3 gold
	vector<const wchar_t *>SavePseudo; //All pseudo of all player
	const wchar_t *savePlay;
	string PathCube;
	string PathWall;
	map<int, int> PlayerIA;
	public:
	Config();
	string getPathCube() const;
	string getPathWall() const;
	map<int, int> getPlayerIA();
	const wchar_t *getSavePlay() const;
	vector<const wchar_t *> getSavePseudo();
	void SaveNbrPlayer(vector<irr::gui::IGUIButton *>);
	void SaveColor(map<int, int>, vector<irr::gui::IGUIButton *> ButtonDelAdd);
	void SaveName(vector<irr::gui::IGUIEditBox *>);
	void FileSave(const wchar_t *);

	int getNbrPlayer() const;
	map<int, int> getColors();
	vector<const wchar_t *> getPseudos();

	void SavePathCube(int, int);
	void SaveIA(vector<irr::gui::IGUIButton *>);
};

#endif //CPP_INDIE_STUDIO_CONFIG_HPP
