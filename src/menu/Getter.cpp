/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include "Menu.hpp"

char * StrAllocThrowA(size_t cchSize)
{
	return new char[cchSize];
}
wchar_t * StrAllocThrowW(size_t cchSize)
{
	return new wchar_t[cchSize];
}
void StrFreeA(char * s)
{
	delete[] s;
}
void StrFreeW(wchar_t * s)
{
	delete[] s;
}

//Surcharge C++, plus simple.
inline void StrFree( char   * s) { return StrFreeA(s); }
inline void StrFree(wchar_t * s) { return StrFreeW(s); }

//Fonctions de conversion
wchar_t * ambstowcs(char const *sczA)
{
	size_t const cchLenA = strlen(sczA);
	size_t const cchLenW = mbstowcs(NULL, sczA, cchLenA+1);
	wchar_t * szW = StrAllocThrowW(cchLenW+1);
	mbstowcs(szW, sczA, cchLenA+1);
	return szW;
}

irr::IrrlichtDevice 	*Menu::getDevice()
{
	return (device);
}
