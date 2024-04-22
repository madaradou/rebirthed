#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

int scale =5;
void initMap(Minimap *m) {
    m->image = SDL_LoadBMP("minibackground.bmp");
    if (m->image == NULL) {
        printf("Erreur lors du chargement de l'image de la minimap : %s\n", SDL_GetError());
    }
    
    // Ajuster la position de la minimap
   m->pos.x = (1536 -MINIMAP_WIDTH)/2;//coin superieur droite
   m->pos.y = 10;

}
void initialiser_minimap_perso(Minimap *m, Personne *P){
    m->img_bon=IMG_Load("image1.png");
    m->pos_bon.x=(1536- MINIMAP_WIDTH) +(P->pos.x/scale);
    m->pos_bon.y=(803 - MINIMAP_HEIGHT)+(P->pos.y/scale);
    m->pos_bon.w=P->pos.w/scale;
    m->pos_bon.h=P->pos.h/scale;
}

void MAJMinimap(SDL_Rect posJoueur,  Minimap * m, SDL_Rect camera, int redimensionnement){
    SDL_Rect posJoueurABS;

    posJoueurABS.x=posJoueur.x + camera.x;
    posJoueurABS.y=posJoueur.y + camera.y;

    m->pos_bon.x=posJoueurABS.x * redimensionnement/100;
    m->pos_bon.y=posJoueurABS.y * redimensionnement/100;

}
/*void afficherBonhomme(Minimap m, SDL_Surface *screen) {
    // Dessiner la miniature du bonhomme sur la surface de la minimap
    SDL_BlitSurface(m.img_bon, NULL, screen, &m.pos_bon);
}*/


void afficherminimap(Minimap m, SDL_Surface *screen) {
    
    SDL_BlitSurface(m.image, NULL, screen, &m.pos);
    SDL_BlitSurface(m.img_bon,NULL,m.image,&m.pos_bon);
   
}

void affichertemps(SDL_Surface* screen, int temps) {
    temps=0;
    int currentTime = SDL_GetTicks();
    int elapsedTime = (currentTime - temps) / 1000; // Convertir en secondes
    TTF_Init();

    
    TTF_Font* font = TTF_OpenFont("oldparisnouveautitling.ttf", 24); 

    
    SDL_Color color = {255, 0, 0}; // Rouge

    // Créer une surface de texte à partir du temps écoulé
    char timeString[20]; // Chaîne de caractères pour stocker le temps
    sprintf(timeString, "Temps : %d s", elapsedTime); // Formater la chaîne de caractères avec le temps écoulé
    SDL_Surface* timeSurface = TTF_RenderText_Solid(font, timeString, color); // Créer la surface de texte

    
    SDL_Rect textPos;
    textPos.x = 100; // Position en X
    textPos.y = 0; // Position en Y
    SDL_BlitSurface(timeSurface, NULL, screen, &textPos);

    SDL_FreeSurface(timeSurface);
    TTF_CloseFont(font);
}


SDL_Color GetPixel(SDL_Surface *pSurface, int x,int y){
    SDL_Color color;

    Uint32 col=0;

    //Determine position
    char *pPosition=(char* ) pSurface->pixels;
    pPosition+= (pSurface->pitch * y);

    pPosition+= (pSurface->format->BytesPerPixel *x);

    memcpy(&col ,pPosition, pSurface->format->BytesPerPixel);

    //convertir color

    SDL_GetRGB(col,pSurface->format, &color.r, &color.g, &color.b);

    return (color);
}


 int CollisionPP(Personne p, SDL_Surface* masque) {
    // Définir la couleur du masque (noir)
    SDL_Color Couleur_Masque = {0, 0, 0, 255}; // Noir

    // Définir les positions de référence
    SDL_Rect Pos[8];
    Pos[0].x = p.pos.x;
    Pos[0].y = p.pos.y;
    Pos[1].x = p.pos.x;
    Pos[1].y = p.pos.y;
    Pos[2].x = (p.pos.x + p.img->w) / 2;
    Pos[2].y = p.pos.y;
    Pos[3].x = (p.pos.x + p.img->w);
    Pos[3].y = p.pos.y;
    Pos[4].x = p.pos.x;
    Pos[4].y = (p.pos.y + p.img->h) / 2;
    Pos[5].x = p.pos.x;
    Pos[5].y = (p.pos.y + p.img->h);
    Pos[6].x = (p.pos.x + p.img->w) / 2;
    Pos[6].y = (p.pos.y + p.img->h);
    Pos[7].x = (p.pos.x + p.img->w);
    Pos[7].y = (p.pos.y + p.img->h) / 2;

    // Vérifier la collision pour chaque position de référence
    for (int i = 0; i < 8; i++) {
        // Récupérer la couleur à la position de référence
        SDL_Color Couleur_Position = GetPixel(masque, Pos[i].x, Pos[i].y);
        
        // Si la couleur à la position de référence est égale à la couleur du masque (noir)
        if (Couleur_Position.r == Couleur_Masque.r &&
            Couleur_Position.g == Couleur_Masque.g &&
            Couleur_Position.b == Couleur_Masque.b) {
            return 1; // Collision détectée
        }
    }

    return 0; // Aucune collision détectée
}



int previousTime = 0; // Variable globale pour stocker le temps du dernier clignotement

void animerMinimap(Minimap *m) {
    int isVisible = 1; // Variable pour contrôler la visibilité des rectangles (1 pour visible, 0 pour invisible)
    const int blinkInterval = 500; // Intervalle de clignotement en millisecondes
    SDL_Surface *background = SDL_LoadBMP("minibackground.bmp");

    int currentTime = SDL_GetTicks();

    if (currentTime - previousTime >= blinkInterval) {
        // Inverser la visibilité des rectangles
        isVisible = !isVisible;
        // Mettre à jour le temps du dernier clignotement
        previousTime = currentTime;
    }

    if (isVisible) {
        // Dessiner les rectangles colorés
        SDL_Rect rect1;
        rect1.x = 100; // Position X du premier rectangle
        rect1.y = 100; // Position Y du premier rectangle
        rect1.w = 20;  // Largeur du premier rectangle
        rect1.h = 30;  // Hauteur du premier rectangle
        SDL_FillRect(m->image, &rect1, SDL_MapRGB(m->image->format, 255, 0, 0)); // Remplir le rectangle avec la couleur rouge

        SDL_Rect rect2;
        rect2.x = 130; // Position X du deuxième rectangle
        rect2.y = 100; // Position Y du deuxième rectangle
        rect2.w = 30;  // Largeur du deuxième rectangle
        rect2.h = 20;  // Hauteur du deuxième rectangle
        SDL_FillRect(m->image, &rect2, SDL_MapRGB(m->image->format, 0, 255, 0)); // Remplir le rectangle avec la couleur verte
    } else {
        // Afficher le fond de la minimap lorsque les rectangles ne sont pas visibles
        SDL_BlitSurface(background, NULL, m->image, NULL);
    }
}


/*void sauvegarder(Minimap m, char *nomfichier) {
    FILE *f = fopen(nomfichier, "wb");
    if (f) {
        fwrite(&m, sizeof(Minimap), 1, f);
        fclose(f);
    } else {
        printf("Erreur lors de la sauvegarde du fichier %s\n", nomfichier);
    }
}

void charger(Minimap *m, char *nomfichier) {
    FILE *f = fopen(nomfichier, "rb");
    if (f) {
        fread(m, sizeof(Minimap), 1, f);
        fclose(f);
    } else {
        printf("Erreur lors du chargement du fichier %s\n", nomfichier);
    }
}*/
void Liberer (Minimap * m){
    SDL_FreeSurface(m->image);
    SDL_FreeSurface(m->img_bon);
}