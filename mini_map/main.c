#include <stdio.h>
#include <stdlib.h>
#include"map.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>



int main(){
    Minimap m;
    int quit=0;
    int temps=SDL_GetTicks();
    int redimensionnement=20;
    Personne p;
    SDL_Rect posJoueurABS,posJoueur,camera,posimg;
    SDL_Surface *image;
    SDL_Surface *screen;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Echec d'initialisation de SDL : %s\n", SDL_GetError());
		return 1;
	
	}

    screen=SDL_SetVideoMode(1536, 803,  32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(screen==NULL){
        fprintf(stderr, "Echec de creation de la fenetre de 300*300: %s.\n", SDL_GetError());
        return 1;
    }
    SDL_Surface *background = SDL_LoadBMP("background.bmp");
    if (background == NULL) {
        printf("Erreur lors du chargement de l'image de fond : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    /*m.img_bon=SDL_LoadBMP("icone1.bmp");
    if (m.img_bon == NULL) {
        printf("Erreur lors du chargement de l'image du bonhomme : %s\n", SDL_GetError());
        //SDL_FreeSurface(m.image); // Libérer la surface de la minimap en cas d'erreur
        return 1;
    }*/

    

    initMap(&m);
    initialiser_minimap_perso(&m,&p);
    while(!quit){

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        temps = SDL_GetTicks();

        

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(background,NULL,screen,NULL);
        afficherminimap(m,screen);
        animerMinimap(&m);
        MAJMinimap(posJoueur,&m,camera,redimensionnement);
        //afficherBonhomme(m,screen);
        affichertemps(screen, temps);
         SDL_Flip(screen);
         SDL_Delay(16);


    }
    SDL_FreeSurface(background);
    //SDL_FreeSurface(m.img_bon);
    Liberer(&m);
    SDL_Quit();


    return 0;
}