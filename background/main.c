#include "game.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <stdlib.h>



#define FPS 60

int main(int argc, char *argv[]) {
    SDL_Surface *screen = NULL;
    SDL_Event event;
    int quit =1;
    Mix_Music *music = NULL;
    int scrollDirection = 0; // 0: No scrolling, 1: Left, 2: Right
    JR jr;

    SDL_WM_SetCaption("please madame a3tini note behya", NULL);
    
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)
    {
        printf("could not initialize SDL: %s.\n",SDL_GetError());
        return -1;
    }
    printf("sdl inisialized\n");
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if (screen == NULL) {
        printf("Failed to set up screen: %s\n", SDL_GetError());
        return 1;
    }
    printf("screen intiliazed\n");
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    
    //inisialisation background
    
    background bg;
    background bg_left, bg_right;
    
    initialiser_background(&bg, screen, 0);
    
    

    initefeu(&bg_left, 0); // Initialize left animation
    initefeu(&bg_right, 1); // Initialize right animation
    printf("background initialized\n");
    
    //initialize audio 
    initialiser_audio(music);
    printf("music was just inisilized\n");
    init_sound_player(&jr);
    


    // Main loop
    while (quit) 
    {
        Uint32 start = SDL_GetTicks();

        // Event handling
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                quit = 0;
            }
            // Handle other events here (e.g., key presses for scrolling)
            else if (event.type == SDL_KEYDOWN) 
            {
                switch (event.key.keysym.sym) 
                {
                    case SDLK_LEFT:
                        scrollDirection = 1; // Scroll left
                        break;
                    case SDLK_RIGHT:
                        scrollDirection = 2; // Scroll right
                        break;
                    case SDLK_DOWN :
                        scrollDirection = 3; // Scroll down
                        break;
                    case SDLK_UP :
                        scrollDirection = 4; // Stop up
                        break;
                    // Add more cases for additional keys if needed
                }
            }
            // Handle key releases to stop scrolling
                else if (event.type == SDL_KEYUP) 
                {
                    switch (event.key.keysym.sym) 
                    {
                        case SDLK_LEFT:
                            scrollDirection = 0; // Stop scrolling
                            break;
                        case SDLK_RIGHT:
                            scrollDirection = 0; // Stop scrolling
                            break;
                        case SDLK_DOWN :
                            scrollDirection = 0; // Stop scrolling
                            break;
                        case SDLK_UP :
                            scrollDirection = 0; // Stop scrolling
                            break;

                        // Add more cases for additional keys if needed
                    }
                }
    }

    // Scroll based on the direction
    switch (scrollDirection) 
    {
        case 1:
            scrolling_bg(2, &bg); // Scroll left
            break;
        case 2:
            scrolling_bg(1, &bg); // Scroll right
            break;
        case 3:
            scrolling_bg(3, &bg); // Scroll down
            break;
        case 4:
            scrolling_bg(4, &bg); // Scroll up
            break;
    }
        //animation update
        animerBack(&bg_left);
        animerBack(&bg_right);
        
       
        
        
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        afficher_background(bg, screen);
        afficheranim(bg_left, screen);
        afficheranim(bg_right, screen);

        //sound effects
        controlSounds(event,&quit,&jr);
        SDL_Flip(screen); // Flip buffer

        // Cap frame rate
        if (1000 / FPS > SDL_GetTicks() - start) 
        {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
        }
        
    }


    // Clean up
    liberer_musique(music);
    SDL_FreeSurface(bg.img_bg);
    free_anim(&bg_left);
    free_anim(&bg_right);
    IMG_Quit();
    SDL_Quit();

    return 0;
}