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



double min(double a, double b);

void InitJR(JR *jr);

void AffJR(JR *jr, SDL_Surface *screen, int *nb_skin);

void ConJR(JR *jr, SDL_Event event, int *quit, int *curren_screen);


void MoveJR(JR *jr);

void DrawScore(SDL_Surface *screen, int score);

void jrPlaySound(JR *jr, char *sound_type);

int random_between(int min, int max);

void PlayerShowDots(SDL_Surface *screen, JR *player);


void takeDamage(JR *player, int damage);

void playerDeath(JR *jr);


#endif // PLAYER_H_INCLUDED
