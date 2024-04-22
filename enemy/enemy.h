#ifndef ENEMY_H
#define ENEMY_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h> 
#include <stdio.h>
#include <math.h> 

typedef struct 
{
    SDL_Rect pos1;
    SDL_Rect pos2;
   // SDL_Surface* sprite;
    SDL_Surface* idel_r[25],*run_r[25],* attack_r[25],*hit_r[25] ,* die_r[25];
    SDL_Surface* idel_l[25], *run_l[25],*attack_l[25],* hit_l[25] ,*die_l[25];
    int hp;
    int direction;
    int lvl;
    float collision;
    int imgnum;
    int frame;
    int state;

}Entity;
typedef struct 
{
    SDL_Rect pos;
    SDL_Surface* rotation[25];
    float collision;
    int bonus;
    int imgnumb;
    int frameb;
}bonus;

void initEntity(Entity *e, bonus *b);
void afficherEnnemi(Entity e, bonus b , SDL_Surface  * screen); 
int collisionTri( bonus b,  SDL_Rect pose);
void move( Entity * e,bonus*b);
int collisionBB( Entity e,  SDL_Rect pose);
void moveIA( Entity * e);
#endif