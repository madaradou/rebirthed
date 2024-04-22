#ifndef ENEMY_H
#define ENEMY_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h> 
#include <stdio.h>
#include <math.h> 
#include "structs.h"



void initEntity(Entity *e, bonus *b);
void afficherEnnemi(Entity e, bonus b , SDL_Surface  * screen); 
int collisionTri( bonus b,  SDL_Rect pose);
void move( Entity * e,bonus*b);
int collisionBB( Entity e,  SDL_Rect pose);
void moveIA( Entity * e);
#endif