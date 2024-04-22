#ifndef LEVELS_H
#define LEVELS_H

#include "structs.h"

void initLevel(Level *lvl, int lvl_nb);

void aficherLevel(Background *lvl, SDL_Surface * screen, int x, int y) ;

SDL_Surface *bgPart(SDL_Surface *lvl, int x, int y);

void scrolling(Level *lvl, char *direction, float speed);


#endif
