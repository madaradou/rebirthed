
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <string.h>
#include "levels.h"
#include "player.h"
#include "assets.h"



void initLevel(Level *lvl, int lvl_nb) {
    if (lvl_nb == 1)
    {
        //lvl->lvl1.bg = IMG_Load("bg.png");
        //lvl->lvl1.bg = SDL_DisplayFormatAlpha(lvl->lvl1.bg);
        //lvl->lvl1.bgmask = IMG_Load("bgm.png");
        //lvl->lvl1.bgmask = SDL_DisplayFormatAlpha(lvl->lvl1.bgmask);
        lvl->lvl1.bg = SDL_LoadBMP("assets/levels/level 1/background_7anena_3-dMTr1n6M8-transformed.bmp");
        lvl->lvl1.bgmask = SDL_LoadBMP("assets/levels/level 1/maskkbir.bmp");
        lvl->pos_x = 0;
        lvl->pos_y =  lvl->lvl1.bg->h-SCREEN_H;//0

        lvl->difficulty = 1;
        lvl->lvl1.first_show = 1;

        lvl->solid[0] = 0;//124;
        lvl->solid[1] = 0;//189;
        lvl->solid[2] = 0;//0;

        //music
        
        lvl->lvl1.music = Mix_LoadMUS("assets/levels/level 1/music.mp3");

    }
}
 
SDL_Surface *bgPart(SDL_Surface *lvl, int x, int y){  
    // Create a surface to hold the part of the image we want to blit
    SDL_Rect src_rect = { x, y, WINDOW_H, WINDOW_W }; // x, y, w, h
    SDL_Surface *part_img = NULL;
    part_img = SDL_CreateRGBSurface(lvl->flags, src_rect.w, src_rect.h,
                                                  lvl->format->BitsPerPixel,
                                                  lvl->format->Rmask, lvl->format->Gmask,
                                                  lvl->format->Bmask, lvl->format->Amask);
    
    // Copy the desired part of the image to the new surface
    SDL_BlitSurface(lvl, &src_rect, part_img, NULL);

    return part_img;

}

void aficherLevel(Background *lvl, SDL_Surface * screen, int x, int y) {
    SDL_Rect dest_rect = { 0, 0, 0, 0};
    
    SDL_Surface *part_img = bgPart(lvl->bg, x, y);
    //SDL_Surface *upimg = bgPart(lvl->bgmask, x, y);
    
    SDL_BlitSurface(part_img, NULL, screen, &dest_rect);
    SDL_FreeSurface(part_img);
    
    //SDL_BlitSurface(upimg, NULL, screen, &dest_rect); 

    if (lvl->first_show == 1){
        Mix_PlayMusic(lvl->music, -1);
        lvl->first_show = 0;
    }
}
 
void scrolling(Level *lvl, char *direction, float speed){
    if (strcmp("right",direction) == 0){
        if (lvl->pos_x < lvl->lvl1.bg->w - WINDOW_W){
            lvl->pos_x += speed;
        }

        if (lvl->pos_x > lvl->lvl1.bg->w - WINDOW_W){
            lvl->pos_x = lvl->lvl1.bg->w - WINDOW_W;
        }
    }

    
    
    else if (strcmp("left",direction) == 0){
        if (lvl->pos_x > 0){
            lvl->pos_x += speed;
        }

        if (lvl->pos_x < 0){
            lvl->pos_x = 0;
        }
    }

    else if (strcmp("down",direction) == 0){
        if (lvl->pos_y < lvl->lvl1.bg->h - WINDOW_H){
            lvl->pos_y += speed;
        }

        if (lvl->pos_y > lvl->lvl1.bg->h - WINDOW_H){
            lvl->pos_y = lvl->lvl1.bg->h - WINDOW_H;
        }

    }
    else if (strcmp("up",direction) == 0){
        if (lvl->pos_y > 0){
            lvl->pos_y -= speed;
        }

        if (lvl->pos_y < 0){
            lvl->pos_y = 0;
        }
    }
    
}
