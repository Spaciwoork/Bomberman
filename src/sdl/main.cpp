#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "Noise.hpp"

#define X 512*2
#define Y 512

#define OCTAVES 8
#define PAS 128
#define PERSISTANCE 0.5

void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 obtenirCouleur(double rouge, double vert, double bleu);
Uint32 obtenirPixel(Noise *noise, int x, int y);

int main() {
    SDL_Surface *ecran = NULL, *img = NULL;
    SDL_Rect position;
    Noise noise(X + 1, Y + 1, PAS, OCTAVES);

    // On initialise la SDL.
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(X, Y, 32,  SDL_ANYFORMAT | SDL_HWSURFACE );
    SDL_WM_SetCaption("Test Bruit cohérent", NULL);

    // On crée une surface SDL pour dessiner dedans.
    img = SDL_CreateRGBSurface(SDL_HWSURFACE, X, Y, 32, 0, 0, 0, 0);

    //noise.initBruit2D(TAILLE + 1, TAILLE + 1, PAS, OCTAVES);

    int x,y;
    for(y = 0; y < Y; y++)
	    for(x = 0; x < X; x++){
		    definirPixel(img, x, y, obtenirPixel(&noise, x, y));
	    }
    /* ************ Affichage du résultat **************** */

    position.x = position.y = 0;
    SDL_BlitSurface(img, NULL, ecran, &position);

    // On force l'affichage.
    SDL_Flip(ecran);

    // On attend que l'utilisateur quitte.
    SDL_Event event;
    do
        SDL_WaitEvent( &event );
    while ( event.type!= SDL_QUIT);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    int opp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * opp;

    switch(opp) {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *) p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            * (Uint32 *) p = pixel;
            break;
    }
}

Uint32 obtenirCouleur(double rouge, double vert, double bleu) {
   return (((int) (rouge * 255)) << 16) + (((int) (vert * 255)) << 8) + (int) (bleu * 255);
}

Uint32 obtenirPixel(Noise *noise, int x, int y) {
    double valeur = noise->bruit_coherent2D(x, y);
    if (valeur > 0.5)
	    return obtenirCouleur(valeur, valeur, valeur);
    return (0);
}
