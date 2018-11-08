/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Noise.hpp"

const double pi = 3.14159265;

Noise::Noise(int l, int h, int p, int n)
{
	srand(1527604103);
	srand(time(NULL));
	_nombre_octaves2D = n;
	if(_taille != 0)
		free(_valeurs2D);
	_longueur = h;
	_hauteur = l;
	_persistance = 0.99;
	_pas2D = p;
	_longueur_max = (int) ceil(_longueur * pow(2, _nombre_octaves2D  - 1)  / _pas2D);
	int hauteur_max = (int) ceil(_hauteur * pow(2, _nombre_octaves2D  - 1)  / _pas2D);

	_valeurs2D = (double*) malloc(sizeof(double) * _longueur_max * hauteur_max);

	int i;
	for(i = 0; i < _longueur_max * hauteur_max; i++)
		_valeurs2D[i] = ((double) rand()) / RAND_MAX;
}

Noise::~Noise()
{
	if(_longueur != 0)
		free(_valeurs2D);
        _longueur = 0;
}

void Noise::initBruit1D(int t, int p, int n) {
	_nombre_octaves1D = n;
	if(_taille != 0)
		free(_valeurs1D);
	_taille = t;
	_pas1D = p;
	
	_valeurs1D = (double*) malloc(sizeof(double) * (int) ceil(_taille * pow(2, _nombre_octaves1D  - 1)  / _pas1D));
	
	srand(time(NULL));
	int i;
	for(i = 0; i < ceil(_taille *  pow(2, _nombre_octaves1D  - 1)  / _pas1D); i++)
		_valeurs1D[i] = (double) rand() / RAND_MAX;
}

void Noise::destroyBruit1D() {
	if(_taille != 0)
		free(_valeurs1D);
	_taille = 0;
}

double Noise::bruit1D(int i) {
	return _valeurs1D[i];
}

double Noise::interpolation_cos1D(double a, double b, double x) {
	double k = (1 - cos(x * pi)) / 2;
	return a * (1 - k) + b * k;
}

double Noise::fonction_bruit1D(double x) {
	int i = (int) (x / _pas1D);
	return interpolation_cos1D(bruit1D(i), bruit1D(i + 1), fmod(x / _pas1D, 1));
}


double Noise::bruit_coherent1D(double x, double persistance) {
	double somme = 0;
	double p = 1;
	int f = 1;
	int i;
	
	for(i = 0 ; i < _nombre_octaves1D ; i++) {
		somme += p * fonction_bruit1D(x * f);
		p *= persistance;
		f *= 2;
	}
	return somme * (1 - persistance) / (1 - p);
}

void Noise::initBruit2D(int l, int h, int p, int n) {
	_nombre_octaves2D = n;
	if(_taille != 0)
		free(_valeurs2D);
	_longueur = l;
	_hauteur = h;
	_pas2D = p;
	_longueur_max = (int) ceil(_longueur * pow(2, _nombre_octaves2D  - 1)  / _pas2D);
	int hauteur_max = (int) ceil(_hauteur * pow(2, _nombre_octaves2D  - 1)  / _pas2D);
	
	_valeurs2D = (double*) malloc(sizeof(double) * _longueur_max * hauteur_max);
	
	int i;
	for(i = 0; i < _longueur_max * hauteur_max; i++)
		_valeurs2D[i] = ((double) rand()) / RAND_MAX;
}

void Noise::destroyBruit2D() {
	if(_longueur != 0)
		free(_valeurs2D);
	_longueur = 0;
}

double Noise::bruit2D(int i, int j) {
	return _valeurs2D[i * _longueur_max + j];
}

double Noise::interpolation_cos2D(double a, double b, double c, double d, double x, double y) {
	double y1 = interpolation_cos1D(a, b, x);
	double y2 = interpolation_cos1D(c, d, x);
	return  interpolation_cos1D(y1, y2, y);
}
double Noise::fonction_bruit2D(double x, double y) {
	int i = (int) (x / _pas2D);
	int j = (int) (y / _pas2D);
	return interpolation_cos2D(bruit2D(i, j), bruit2D(i + 1, j), bruit2D(i, j + 1), bruit2D(i + 1, j + 1), fmod(x / _pas2D, 1), fmod(y / _pas2D, 1));
}

double Noise::bruit_coherent2D(double x, double y) {
	double somme = 0;
	double p = 1;
	int f = 1;
	int i;
	
	for(i = 0 ; i < _nombre_octaves2D ; i++) {
		somme += p * fonction_bruit2D(x * f, y * f);
		p *= _persistance;
		f *= 2;
	}
	return somme * (1 - _persistance) / (1 - p);
}
