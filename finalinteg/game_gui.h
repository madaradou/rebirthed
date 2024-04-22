#ifndef GAME_GUI_H_INCLUDED
#define GAME_GUI_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>

void InitPlayerGui(GameGUI *g_gui, JR *player);

void ShowPlayerGui(GameGUI *g_gui, JR *player, SDL_Surface *screen);



#endif // GAME_GUI_H_INCLUDED