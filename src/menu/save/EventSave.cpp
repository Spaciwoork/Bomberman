/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "EventSave.hpp"

#if WIN32
void Save::open_save()
{
	HANDLE hFind;
	WIN32_FIND_DATA data;
	char *tmp;
	wchar_t *convert;

	hFind = FindFirstFile(FILEPATH "save", &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (strncmp(data.cFileName, ".", 1)) {
				tmp = data.cFileName;
				convert = ambstowcs(tmp);
				list_files.push_back(convert);
			}
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
	else
		std::cout << "Could not open current directory" << std::endl;
}
#else
void Save::open_save()
{
	char *tmp;
	wchar_t *convert;
	struct dirent *de;
	DIR *dr = opendir(FILEPATH "save");
	if (dr == NULL) {
		std::cout << "Could not open current directory" << std::endl;
		return;
	}
	while ((de = readdir(dr)) != NULL) {
		if (strncmp(de->d_name, ".", 1)) {
			tmp = de->d_name;
			convert = ambstowcs(tmp);
			list_files.push_back(convert);
		}
	}
}
#endif

void 	Config::FileSave(const wchar_t *file_selected)
{
	savePlay = file_selected;
}

void	Save::delete_element(Config &configuration)
{
	configuration.FileSave(file_selected);
	ButtonSave.at(0)->remove();
	ButtonSave.clear();
	box->remove();
}

void	EventSave(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, Config &configuration)
{
	Save save;

	save.InitContentSave(device, driver);
	save.LoopSave(device, driver);
	save.delete_element(configuration);	
	return;
}
