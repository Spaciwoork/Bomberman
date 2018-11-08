/*
** EPITECH PROJECT, 2018
** cpp
** File description:
**
*/

#ifndef NOISE_HPP_
# define NOISE_HPP_

//#define TAILLE 512*2
//#define X 512*2
//#define Y 512
// On définit le nombre d'octaves.                                                            
//#define OCTAVES 8
// On définit le pas.                                                                         
//#define PAS 128
// On définit la persistance.                                                                 
//#define PERSISTANCE 0.5

class Noise
{
private:
	double _persistance;
	int _pas1D = 0;
	int _nombre_octaves1D = 0;
	int _taille = 0;
	double* _valeurs1D = NULL;
	
	int _pas2D = 0;
	int _nombre_octaves2D = 0;
	int _hauteur = 0;
	int _longueur = 0;
	int _longueur_max = 0;
	double* _valeurs2D = NULL;
public:
	Noise(int longueur, int hauteur, int pas, int octaves);
	virtual ~Noise();
	void initBruit1D(int longueur, int pas, int octaves);
	double bruit_coherent1D(double x, double persistance);
	void destroyBruit1D();
	double bruit1D(int i);
	double interpolation_cos1D(double a, double b, double x);
	double fonction_bruit1D(double x);

	void initBruit2D(int longueur, int hauteur, int pas, int octaves);
	double bruit_coherent2D(double x, double y);
	void destroyBruit2D();
	double bruit2D(int i, int j);
	double interpolation_cos2D(double a, double b, double c, double d, double x, double y);
	double fonction_bruit2D(double x, double y);
};
#endif
