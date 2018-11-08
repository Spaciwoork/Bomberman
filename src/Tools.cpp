//
// EPITECH PROJECT, 2018
// Tools
// File description:
// Tools
//

#include "Tools.hpp"

int Tools::getNbrRandom(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}

std::vector<std::string> Tools::explode(const std::string &str, const std::string &separator)
{
 	std::vector< std::string > result;
        size_t pos1 = 0;
        size_t pos2 = 0;

	while (pos2 != str.npos){
                pos2 = str.find(separator, pos1);
                if (pos2 != str.npos)
		{
                        if (pos2 > pos1)
                                result.push_back(str.substr(pos1, pos2 - pos1));
 	                pos1 = pos2 + 1;
                }
        }
        result.push_back(str.substr(pos1, str.size() - pos1));
        return result;
}

std::string Tools::getFile(std::string file_name)
{
	std::ifstream file(file_name.c_str(), std::ios::in);
	std::string str;

        if (file)
        {
		std::string line;
		while (getline(file, line)){
			str = str + line + "\n";
		}
                file.close();
        }
	return (str);
}

void Tools::putFile(std::string file_name, std::string content)
{
	std::fstream file(file_name.c_str(), std::ios::out | std::ios::trunc);

	if (file){
		file << content;
		file.close();
	}
}
