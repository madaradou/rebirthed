#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>
#include <SDL/SDL_rotozoom.h>



#include "structs.h"
#include "assets.h"
#include "menu.h"
#include "player.h"
#include "game_gui.h"
#include "levels.h"
#include "map.h"
#include "image.h"
#include "enigme.h"
#include "enemy.h"




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
    

    
/////////////////////////////////////////////////////////////////////xo
    Image background;
    tic game;
    Winner Backg;
    Loser BackgLoser;
    Animation anim;
    const char *framePaths[] = {"assets/tic/backgrounds/animation/yassine.jpg", "assets/tic/backgrounds/animation/2.jpg", "assets/tic/backgrounds/animation/7.jpg", "assets/tic/backgrounds/animation/3.jpg", "assets/tic/backgrounds/animation/4.jpg", "assets/tic/backgrounds/animation/5.jpg"};
    // Initialize background
    initBackground(&background);
    initBackgroundwinner(&Backg);
    initBackgroundLoser(&BackgLoser);

    // Initialize game
    for (int i = 0; i < NUM_SQUARES; i++) {
        game.tabsuivi[i] = 0;
    }
    game.currentTurn = 0;

    // Load font
    TTF_Font* font = TTF_OpenFont("assets/tic/fonts/modartial.ttf", 140);
    if (font == NULL) {
        fprintf(stderr, "Failed to load font! TTF_Error: %s\n", TTF_GetError());
        return 1;
    }

    // Render text
    SDL_Color color = {255, 255, 0};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "GG Winner", color);

    // Initialize animation
    initAnimation(&anim, framePaths);








//////////////////////////////////////////////////////////enigme
enigme e;
int interface = 4; 
    //SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_WM_SetCaption("REBIRTH", NULL);
	initialiserEnigme(&e);
	genererEnigme(&e);
	Mix_PlayMusic(e.musique_enigme, -1);









////////////////////////////////////////////////////////
//menu stuff
     Sprites sprites;
    loadAllSprites(&sprites);   

    Sounds sounds;

    loadAllSounds(&sounds);

    MainMenu main_menu;

    initMenu(&main_menu, sprites);

    int curren_screen = 1;
    int music_channel;
    //playMusic(sounds.mainMenuMusic);

    
    
    
    


    // player stuff
    JR jr, jr2;
    int damage = 10;
    int nb_skin;
    int nb_skin1 = 1;
    int nb_skin2 = 2;
    float delta_s = 0.018;
    InitJR(&jr);
    InitJR(&jr2);
    //init GUI
    GameGUI game_gui;
    InitPlayerGui(&game_gui, &jr);
    

    //controls
    
    jr.keys.left = SDLK_LEFT;
    jr.keys.right = SDLK_RIGHT; 
    jr.keys.jump = SDLK_SPACE;
    jr.keys.attack = SDLK_d;
    jr.keys.special = SDLK_f;
    jr.keys.shield = SDLK_LSHIFT;

    jr2.keys.left = SDLK_k;
    jr2.keys.right = SDLK_m; 
    jr2.keys.jump = SDLK_l;
    jr2.keys.attack = SDLK_b;
    jr2.keys.special = SDLK_n;
    jr2.keys.shield = SDLK_w;
    
    
    //backround init
    Level levels[5];
    initLevel(&levels[0], 1);
  

    //minimap   
    Minimap m;
    int temps = 0;
    initMap(&m);

    initialiser_minimap_perso(&m, &jr);

//////////////////////////////////////////enemy
    Entity entity; // Declare an Entity variable
    bonus bon;
    // Initialize the Entity using the initEntity function
    initEntity(&entity,&bon);

/////////////////////////////////////////







    // Main game loop
    int quit = 0;
    SDL_Event event;
    while (!quit) {

            showMenu(&main_menu, screen, &event, sounds, &quit, &curren_screen, &nb_skin, &jr.keys);
            
            
            if(curren_screen == 5){
            //Mix_HaltMusic();
            //backround
            aficherLevel(&levels[0].lvl1, screen, levels[0].pos_x, levels[0].pos_y);
            
            //player
            ConJR(&jr, event, &quit, &curren_screen);

            PlayerGetCollisionPoint(&jr, levels[0].lvl1.bgmask);

            PlayerCollisionAndGravity(&jr, &delta_s, &levels[0]);

            //SDL_BlitSurface(ground_image, NULL, screen, &ground_rect);
            ShowPlayerGui(&game_gui, &jr, screen);

            

            //AffJR(&jr, screen, &nb_skin);

           

            
            AffJR(&jr, screen, &nb_skin);
            
           //minimap
            afficherminimap(m,screen);
            
            animerMinimap(&m);

        temps =  SDL_GetTicks();
        affichertemps(screen, temps);

                    afficherEnnemi(entity,bon, screen);
            //SDL_Delay(10);
            move(&entity,&bon);
            SDL_Rect pose= {jr.x, jr.y, jr.h, jr.w};
            if (collisionBB(entity,pose)==1) //player and enemy
             {
                entity.state=2;
                takeDamage(&jr, damage);
             }
            else
            {
                entity.state=5;
            }
            /*int colli;
            colli=0;
            if (collisionTri(bon,pose)==1) //player and enemy
            {
                colli=1;
                /*int i;
                for (i=0;i<=9;i++)
                {
                    SDL_FreeSurface(bon.rotation);
                }
            }
            if (colli==1)
            {
                bon.frameb=10;
                SDL_BlitSurface(bon.rotation[10], NULL, screen, &bon.pos);
            }*/

            
            }
            if(curren_screen == 16){

                 while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
                int row = event.button.y / (SCREEN1_H / 3);
                int col = event.button.x / (SCREEN1_W / 3);
                int index = row * 3 + col;
                if (game.tabsuivi[index] == 0 && game.currentTurn < NUM_SQUARES) {
                    game.tabsuivi[index] = -1;
                    game.currentTurn++;
                }
            }
        }

        // Clear the screen
        //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        // Draw background
        afficher(background, screen);

        // Draw animation
        updateAnimation(&anim);
        drawAnimation(anim, screen);

        // Draw Tic-Tac-Toe grid
        afficherTic(game, screen);

        // Check for winner
        int winner = atilganer(game.tabsuivi);
        if (winner != 0) {
            if (winner == -1) {
                afficherwinner(Backg, screen);
                rotationtext(textSurface, screen, &quit);
                printf("Player %d wins!\n", winner);
            } else if (winner == 1) {
                afficherBackgroundLoser(BackgLoser, screen);
                zoomText(screen, font, color);
                printf("Player %d wins!\n", winner);
            }
        }

        // If it's the computer's turn
        if (game.currentTurn % 2 != 0 && !quit) {
            makeComputerMove(&game);
            game.currentTurn++;
        }

            }



            ///////////////////////
    if (curren_screen == 9){ 

                if (interface == 4) 
        { 
		animerEnigme(&e);
		afficherEnigme(e, screen);
        }

		if (interface == 5) 
		{
			interface_win(screen, &quit, e);
		}

		if (interface == 6) 
		{
			interface_lose(screen, &quit, e);
		}
			
		while (SDL_PollEvent(&event))
		{	

			switch (event.type)
			{
				case SDL_QUIT :
					quit = 1;
					break;
					

				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE :
							quit = 1;
							break;

						case SDLK_KP0 :
						case SDLK_0 :
							if (e.ReponseCorrecte == 0) interface = 5;
							else interface = 6;
							break;

						case SDLK_KP1 :
						case SDLK_1 :
							if (e.ReponseCorrecte == 1) interface = 5;
							else interface = 6;
							break;

						case SDLK_KP2 :
						case SDLK_2 :
							if (e.ReponseCorrecte == 2) interface = 5;
							else interface = 6;
							break;

						case SDLK_KP3 :
						case SDLK_3 :
							if (e.ReponseCorrecte == 3) interface = 5;
							else interface = 6;
							break;

						case SDLK_KP4 :
						case SDLK_4 :
							if (e.ReponseCorrecte == 4) interface = 5;
							else interface = 6;
							break;

						case SDLK_KP5 :
						case SDLK_5 :
							if (e.ReponseCorrecte == 5) interface = 5;
							else interface = 6;
							break;

						case SDLK_KP6:
						case SDLK_6:
							if (e.ReponseCorrecte == 6) interface = 5;
							else interface = 6;
							break;

						case SDLK_KP7 :
						case SDLK_7 :
							if (e.ReponseCorrecte == 7) interface = 5;
							else interface = 6;
							break;

						case SDLK_KP8 :
						case SDLK_8 :
							if (e.ReponseCorrecte == 8) interface = 5;
							else interface = 6;
							break;

						case SDLK_KP9 :
						case SDLK_9 :
							if (e.ReponseCorrecte == 9) interface = 5;
							else interface = 6;
							break;
					}
				
			}


                
            }
        }
            }
           
            
            

            

            // Update the screen
            SDL_Flip(screen);

            

            SDL_Delay(10);//////
            
            
            // Clear the screen
            SDL_FillRect(screen, NULL, 0x000000);

            

            

        }
       
    Liberer(&m);
    //backround
    liberer(&background);
    libererwinner(&Backg);
    libererLoser(&BackgLoser);
    freeAnimation(&anim);
   

    // Clean up
    
    TTF_Quit();
    SDL_Quit();

    return 0;
}
