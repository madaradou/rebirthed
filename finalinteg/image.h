
#define IMAGE_H

#define WINNER_H

#define LOSER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>




#define SCREEN1_W 1380
#define SCREEN1_H 820

#define WINNER_SCREEN_W 1400 
#define WINNER_SCREEN_H 900


#define LOSER_SCREEN_W 1400
#define LOSER_SCREEN_H 900
#define TEXT_MAX_SIZE 140
#define NUM_SQUARES 9

typedef struct {
    SDL_Surface *img;
    SDL_Rect pos1;
    SDL_Rect pos2;
} Image;

typedef struct {
    int tabsuivi[NUM_SQUARES];
    int currentTurn;
    SDL_Surface *x_img;
    SDL_Surface *o_img;
    TTF_Font *font;
} tic;

typedef struct {
    SDL_Surface *frames[6]; // Assuming you have 3 frames for the animation
    int currentFrame;
    SDL_Rect pos;
} Animation;

struct winner {
    SDL_Rect pos1; // position relative to the screen
    SDL_Surface* img;
};

typedef struct winner Winner;

struct loser {
    SDL_Rect pos1; // position relative to the screen
    SDL_Surface* img;
};

typedef struct loser Loser;

void initBackground(Image* Backg);
void liberer(Image* A);
void afficher(Image p, SDL_Surface* screen);
void afficherTic(tic t, SDL_Surface* ecran);
int atilganer(int tabsuivi[]);
void Resultat(int tabsuivi[], SDL_Surface* ecran);
void libererMemoire(tic t);
int minimax(int tabsuivi[9], int joueur);
void calcul_coup(int tabsuivi[9]);
void makeComputerMove(tic *t);
void initAnimation(Animation *anim, const char* framePaths[]);
void updateAnimation(Animation *anim);
void drawAnimation(Animation anim, SDL_Surface *screen);
void freeAnimation(Animation *anim);
void initBackgroundwinner(Winner* Backg);
void libererwinner(Winner* A);
void afficherwinner(Winner p, SDL_Surface* screen);
void rotationtext(SDL_Surface* textSurface, SDL_Surface* screen, int* done);
void initBackgroundLoser(Loser* Backg);
void libererLoser(Loser* A);
void eraseSurface(SDL_Surface* screen, SDL_Rect rect);
void afficherLoser(Loser p, SDL_Surface* screen);
void zoomText(SDL_Surface* screen, TTF_Font* font, SDL_Color color);
void afficherBackgroundLoser(Loser BackgLoser, SDL_Surface* screen);




