#include "enemy.h"
int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_image
    if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }
    // Create a window and screen surface
        SDL_Surface* screen = SDL_SetVideoMode(600, 400, 32, SDL_HWSURFACE| SDL_DOUBLEBUF );
        if (screen == NULL) {
            printf("SDL_SetVideoMode Error: %s\n", SDL_GetError());
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    Entity entity; // Declare an Entity variable
    bonus bon;
    SDL_Event event;
    // Initialize the Entity using the initEntity function
    initEntity(&entity,&bon);
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
			        switch (event.key.keysym.sym){
				        case SDLK_ESCAPE:
					    running=0;
				        break;
			            }
		            break;
            }
        }
        
        // Now entity is initialized with the specified values
        //initEntity(&entity,&bon);

        afficherEnnemi(entity,bon, screen);
        SDL_Flip(screen);
        SDL_Delay(100);
        move(&entity,&bon);
        SDL_Rect pose;
        if (collisionBB(entity,pose)==0) //player and enemy
        {
            entity.state=2;
        }
        if (collisionTri(bon,pose)) //money and player
        {
            //SDL_FreeSurface(bon);
        }
        
        // Clear the screen
        //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        
    } 
    //SDL_Flip(screen);
    //SDL_FreeSurface(entity.sprite);// Don't forget to free the surface when you're done with it
    IMG_Quit();// Quit SDL_image
    SDL_Quit();// Quit SDL

    return 0;
}



