#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>


#include "structs.h"
#include "assets.h"
#include "menu.h"
#include "player.h"
#include "game_gui.h"


int main(int argc, char** argv)
{
      if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_image
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG)) {
        fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }
    // Create a window
    SDL_Surface* screen = SDL_SetVideoMode(WINDOW_W , WINDOW_H , 32, SDL_SWSURFACE);
    if (screen == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }



//menu stuff
     Sprites sprites;
    loadAllSprites(&sprites);   

    Sounds sounds;

    loadAllSounds(&sounds);

    MainMenu main_menu;

    initMenu(&main_menu, sprites);

    int curren_screen = 1;
    int music_channel;
    playMusic(sounds.mainMenuMusic);

    
    
    
    


    // player stuff
    JR jr;
    JR jr2;
    int nb_skin = 1;
    int nb_skin2 = 2;

    InitJR(&jr);
    InitJR(&jr2);
    //init GUI
    GameGUI game_gui;
    InitPlayerGui(&game_gui, &jr);
    //controls
    KeyConfig keys;
    jr.keys.left = SDLK_LEFT;
    jr.keys.right = SDLK_RIGHT; 
    jr.keys.jump = SDLK_SPACE;
    jr.keys.attack = SDLK_d;
    jr.keys.special = SDLK_f;
    jr.keys.shield = SDLK_LSHIFT;

    jr2.keys.left = SDLK_k;
    jr2.keys.right = SDLK_m; 
    jr2.keys.jump = SDLK_p;
    jr2.keys.attack = SDLK_b;
    jr2.keys.special = SDLK_n;
    jr2.keys.shield = SDLK_v;

    
    
    //backround init
    SDL_Surface* ground_image = SDL_LoadBMP("assets/backrounds/backround1/ground.bmp");
    SDL_Rect ground_rect = {0, SCREEN_HEIGHT - ground_image->h, ground_image->w, ground_image->h};    

    // Main game loop
    int quit = 0;
    SDL_Event event;
    while (!quit) {

            showMenu(&main_menu, screen, &event, sounds, &quit, &curren_screen, &nb_skin, &keys);
            
            
            if(curren_screen == 5){
            Mix_HaltMusic();
            // player
            

            

            ConJR(&jr, event, &quit, &curren_screen);

            

            SDL_BlitSurface(ground_image, NULL, screen, &ground_rect);
            ShowPlayerGui(&game_gui, &jr, screen);

            

            AffJR(&jr, screen, &nb_skin);

           

            MoveJR(&jr); 
            }
            //end player

            else if(curren_screen == 9){
            Mix_HaltMusic();
            // player
            

            

            ConJR(&jr, event, &quit, &curren_screen);
            ConJR(&jr2, event, &quit, &curren_screen);


            

            SDL_BlitSurface(ground_image, NULL, screen, &ground_rect);
            ShowPlayerGui(&game_gui, &jr, screen);

            

            AffJR(&jr, screen, &nb_skin);
            AffJR(&jr2, screen, &nb_skin);

           

            MoveJR(&jr); 
            MoveJR(&jr2); 
            }
            

            

            // Update the screen
            SDL_Flip(screen);

            

            SDL_Delay(10);//////
            
            
            // Clear the screen
            SDL_FillRect(screen, NULL, 0x000000);

            

            

        }
       
    

    // Clean up
    
    TTF_Quit();
    SDL_Quit();

    return 0;
}
