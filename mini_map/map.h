#ifndef	HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#define MINIMAP_WIDTH 300
#define MINIMAP_HEIGHT 170

typedef struct {
    SDL_Surface* image;
    SDL_Rect pos;
    SDL_Surface* img_bon;
    SDL_Rect pos_bon;
}Minimap;

typedef struct {
    int x;
    int y;
} Position;

/*typedef struct

    SDL_Rect camera_pos;
    int direction;
}Background;*/

typedef struct 
{
    SDL_Surface* img;
    SDL_Rect pos;

}Personne;



void initMap(Minimap *m);

void initialiser_minimap_perso(Minimap *m, Personne *P);

void MAJMinimap(SDL_Rect posJoueur,  Minimap * m, SDL_Rect camera, int redimensionnement);

void afficherBonhomme(Minimap m, SDL_Surface *screen) ;

void afficherminimap (Minimap m, SDL_Surface * screen);

void affichertemps(SDL_Surface* screen, int temps);

SDL_Color GetPixel(SDL_Surface *pSurface, int x,int y);

int CollisionPP(Personne p, SDL_Surface* masque);

void animerMinimap( Minimap * m);

//void sauvegarder (personne p, Background b, char * nomfichier) ; 

//void charger ( personne * p, Background *b , char * nomfichier);

void Liberer (Minimap * m);


#endif // HEADER_H_INCLUDED
