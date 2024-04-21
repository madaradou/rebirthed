#include"map.h"
#include <stdio.h>
#include<stdlib.h>
int scale =5;
void initMap(Minimap *m) {
    m->image = SDL_LoadBMP("minibackground.bmp");
    if (m->image == NULL) {
        printf("Erreur lors du chargement de l'image de la minimap : %s\n", SDL_GetError());
    }
    
    // Ajuster la position de la minimap
   m->pos.x = (1536 -MINIMAP_WIDTH);//coin superieur droite
   m->pos.y = 10;

}
/*void initialiser_minimap_perso(Minimap *m, Personne *P){
    m->img_bon=IMG_Load("image1.png");
    m->pos_bon.x=(1536- MINIMAP_WIDTH) +(P->pos.x/scale);
    m->pos_bon.y=(803 - MINIMAP_HEIGHT)+(P->pos.y/scale);
    m->pos_bon.w=P->pos.w/scale;
    m->pos_bon.h=P->pos.h/scale;
}*/

void MAJMinimap(SDL_Rect posJoueur,  Minimap * m, SDL_Rect camera, int redimensionnement){
    SDL_Rect posJoueurABS;

    posJoueurABS.x=posJoueur.x + camera.x;
    posJoueurABS.y=posJoueur.y + camera.y;

    m->pos_bon.x=posJoueurABS.x * redimensionnement/100;
    m->pos_bon.y=posJoueurABS.y * redimensionnement/100;

}
void afficherBonhomme(Minimap m) {
    // Dessiner la miniature du bonhomme sur la surface de la minimap
    SDL_BlitSurface(m.img_bon, NULL, m.img_bon, &m.pos_bon);
}


void afficherminimap(Minimap m, SDL_Surface *screen) {
    
    SDL_BlitSurface(m.image, NULL, screen, &m.pos);
    //SDL_BlitSurface(m.img_bon,NULL,m.image,&m.pos_bon);

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


Uint32 GetPixel(SDL_Surface* surface, int x, int y) {
    // Récupérer la couleur du pixel à la position (x, y)
    Uint32 pixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * sizeof(Uint32);
    pixel = *(Uint32 *)p;
    return pixel;
}


 int CollisionPP(Personne p, SDL_Surface* masque) {
    // Vérifier si la position de p est dans les limites du masque
    if ((p.pos.x >= 0 && p.pos.x + p.img->w <= masque->w) && (p.pos.y >= 0 && p.pos.y + p.img->h <= masque->h)) {
        // Stocker la couleur du pixel du masque à différents points autour de la position de p
        Uint32 pp[9];
        pp[0] = GetPixel(masque, p.pos.x, p.pos.y); // Coin supérieur gauche
        pp[1] = GetPixel(masque, p.pos.x, p.pos.y); // Directement au-dessus de p
        pp[2] = GetPixel(masque, (p.pos.x + p.img->w) / 2, p.pos.y); // Centre supérieur
        pp[3] = GetPixel(masque, (p.pos.x + p.img->w), p.pos.y); // Coin supérieur droit
        pp[4] = GetPixel(masque, p.pos.x, (p.pos.y + p.img->h) / 2); // Centre gauche
        pp[5] = GetPixel(masque, p.pos.x, (p.pos.y + p.img->h)); // Directement en dessous de p
        pp[6] = GetPixel(masque, (p.pos.x + p.img->w) / 2, (p.pos.y + p.img->h)); // Centre inférieur
        pp[7] = GetPixel(masque, (p.pos.x + p.img->w), (p.pos.y + p.img->h)); // Coin inférieur droit
        pp[8] = GetPixel(masque, (p.pos.x + p.img->w), (p.pos.y + p.img->h) / 2); // Centre droit

        // Vérifier si l'un des pixels du masque est différent de la couleur transparente
        for (int i = 0; i < 9; i++) {
            if (pp[i] != SDL_MapRGBA(masque->format, 0, 0, 0, 0)) {
                return 1; // Collision détectée
            }
        }
    }

    return 0; // Aucune collision détectée
}




void animerMinimap(Minimap *m) {
    static int isVisible = 1; // Variable pour contrôler la visibilité des rectangles (1 pour visible, 0 pour invisible)
    static int previousTime = 0; // Variable pour stocker le temps du dernier clignotement
    const int blinkInterval = 500;// Intervalle de clignotement en millisecondes
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
}