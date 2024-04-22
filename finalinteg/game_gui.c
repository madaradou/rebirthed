
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "player.h"
#include "game_gui.h"

void InitPlayerGui(GameGUI *g_gui, JR *player){
    int i;

    //init player moves
    int spNB[3] = {11/*healt bar*/, 2/*hearts*/, 11/*player icon*/};//nb of images in each sprite
    
    g_gui->nbStuff = 3;//nb of stuff

    //seting the nb of images to the g_gui struct
    g_gui->sprites_nb_img = (int*) malloc(g_gui->nbStuff * sizeof(int));
    for (i=0; i<g_gui->nbStuff; i++){
        g_gui->sprites_nb_img[i] = spNB[i];
    }
    

    ///init sprites
    char spname[256];

    //heath bar (0)
    for (i=1; i<=g_gui->sprites_nb_img[0]; i++ ){
        sprintf(spname, "assets/sprites/GUI/Health bar/image%d.png", i);
        g_gui->player_health_bar[i-1] = IMG_Load(spname);
    }

    //hearts (1)
    for (i=1; i<=g_gui->sprites_nb_img[1]; i++ ){
        sprintf(spname, "assets/sprites/GUI/Hearts/image%d.png", i);
        g_gui->player_hearts[i-1] = IMG_Load(spname);
    }

    //player icon
    for (i=1; i<=g_gui->sprites_nb_img[2]; i++ ){
        sprintf(spname, "assets/sprites/GUI/face icon/player 1/image%d.png", i);
        g_gui->player_face_icon[i-1] = IMG_Load(spname);
    }

    //infos
    g_gui->x = 0;
    g_gui->y = 0;
    g_gui->w = 0;
    g_gui->h = 0;
    g_gui->max_hearts = player->lives;
    g_gui->currentImgInd =  0;

    //face icon
    g_gui->face_icon_x = 5;
    g_gui->face_icon_y = g_gui->player_face_icon[0]->h;

    g_gui->face_icon_w = g_gui->player_face_icon[0]->w;
    g_gui->face_icon_h = g_gui->player_face_icon[0]->h;

    //hearts
    g_gui->heart_x = g_gui->player_face_icon[0]->h-10;
    g_gui->heart_y = g_gui->player_health_bar[0]->h + 5;

    g_gui->heart_w = g_gui->player_hearts[0]->w;
    g_gui->heart_h = g_gui->player_hearts[0]->h;


}

void ShowPlayerGui(GameGUI *g_gui, JR *player, SDL_Surface *screen){
        if (!player->dead){
            g_gui->currentImgInd = player->health / 10;
        }
        else{
            g_gui->currentImgInd = 0;
        }
        //Draw player health bar
        SDL_Rect health_bar_rect = { g_gui->x, g_gui->y, g_gui->w, g_gui->h };
        SDL_BlitSurface(g_gui->player_health_bar[g_gui->currentImgInd], NULL, screen, &health_bar_rect);

        //Draw player face icon
        SDL_Rect face_icon_rect = { g_gui->face_icon_x, g_gui->face_icon_y, g_gui->face_icon_w, g_gui->face_icon_h };
        SDL_BlitSurface(g_gui->player_face_icon[g_gui->currentImgInd], NULL, screen, &face_icon_rect);

        //Draw player hearts bar
        SDL_Rect hearts_bar_rect = { g_gui->heart_x, g_gui->heart_y, g_gui->heart_w, g_gui->heart_h };
        for (int i=1; i<=g_gui->max_hearts; i++){
            if (i <= player->lives){
                hearts_bar_rect.x = g_gui->heart_x + ((g_gui->heart_w+5) * i-1 );
                SDL_BlitSurface(g_gui->player_hearts[0], NULL, screen, &hearts_bar_rect);
            }
            else{
                hearts_bar_rect.x = g_gui->heart_x + ((g_gui->heart_w+5) * i-1 );
                SDL_BlitSurface(g_gui->player_hearts[1], NULL, screen, &hearts_bar_rect);
            }
        }
        

}





