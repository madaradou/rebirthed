#ifndef PLAYER_H_INCLUDED
#define PLAYER__H_INCLUDED

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>
#include "structs.h"

SDL_Color GetPixel(SDL_Surface *pSurface, int x,int y);

double min(double a, double b);

void InitJR(JR *jr);

int checkCollusion(SDL_Color pp, int item[]);

void AffJR(JR *jr, SDL_Surface *screen, int *nb_skin);

void ConJR(JR *jr, SDL_Event event, int *quit, int *curren_screen);

void PlayerGetCollisionPoint(JR *player, SDL_Surface *ground_image);

void MoveJR(JR *jr);

void DrawScore(SDL_Surface *screen, int score);

void jrPlaySound(JR *jr, char *sound_type);

int random_between(int min, int max);

void PlayerShowDots(SDL_Surface *screen, JR *player);

void Dots(SDL_Surface *screen, int x, int y);

void takeDamage(JR *player, int damage);

void playerDeath(JR *jr, SDL_Surface *screen);

void PlayerCollisionAndGravity(JR *player, float *delta_s, Level *lvl);


#endif // PLAYER_H_INCLUDED
