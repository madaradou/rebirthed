#ifndef	HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>
#define MINIMAP_WIDTH 300
#define MINIMAP_HEIGHT 170
#include "structs.h"






void initMap(Minimap *m);

void initialiser_minimap_perso(Minimap *m, JR *P);

void MAJMinimap(JR player,  Minimap * m, SDL_Rect camera, int redimensionnement);

void afficherBonhomme(Minimap m) ;

void afficherminimap (Minimap m, SDL_Surface * screen);

void affichertemps(SDL_Surface* screen, int temps);

SDL_Color GetPixel2(SDL_Surface *pSurface, int x,int y);

int CollisionPP(Personne p, SDL_Surface* masque);

void animerMinimap(Minimap *m);

//void sauvegarder (personne p, Background b, char * nomfichier) ; 

//void charger ( personne * p, Background *b , char * nomfichier);

void Liberer (Minimap * m);


#endif // HEADER_H_INCLUDED
