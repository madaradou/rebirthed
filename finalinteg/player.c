#include "player.h"
#include "levels.h"
#include "assets.h"


double min(double a, double b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int checkCollusion(SDL_Color pp, int item[]){

    return ( (pp.r == item[0] && pp.g == item[1] && pp.b == item[2]) );
}

int random_between(int min, int max) {
    srand(time(NULL));
    int random_num = rand();
    random_num = (random_num % (max - min + 1)) + min;
    return random_num;
}

SDL_Color GetPixel(SDL_Surface *pSurface, int x,int y){
    SDL_Color color;

    Uint32 col=0;

    //Determine position
    char* pPosition=(char* ) pSurface->pixels;
    pPosition+= (pSurface->pitch * y);

    pPosition+= (pSurface->format->BytesPerPixel *x);

    memcpy(&col ,pPosition, pSurface->format->BytesPerPixel);

    //convertir color

    SDL_GetRGB(col,pSurface->format, &color.r, &color.g, &color.b);
    
    return (color);

}

void InitJR(JR *jr){
    int i;

    //init jr moves
    int spNB[9] = {8/*idel*/, 8/*run*/, 3/*jump*/, 8/*attack*/, 6/*sattack*/, 10/*die*/, 4/*spown*/, 3/*hit*/, 8/*shield*/};//nb of images in each sprite move
    
    jr->nbMoves = 9;//nb of moves

    //seting the nb of images to the jr struct
    jr->sprites_nb_img = (int*) malloc(jr->nbMoves * sizeof(int));
    for (i=0; i<jr->nbMoves; i++){
        jr->sprites_nb_img[i] = spNB[i];
    }
    
    //sprite animation
    jr->currentframe = 0;
    jr->frameDelay = 50;
    jr->nextFrameTime = 0;

    ///init sprites
    char spname[256];

    //idel (0)
    for (i=1; i<=jr->sprites_nb_img[0]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 1/idel/right/image%d.png", i);
        jr->idel_r[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 1/idel/left/image%d.png", i);
        jr->idel_l[i-1] = IMG_Load(spname);
    }

    //run (1)
    for (i=1; i<=jr->sprites_nb_img[1]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 1/run/right/image%d.png", i);
        jr->run_r[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 1/run/left/image%d.png", i);
        jr->run_l[i-1] = IMG_Load(spname);
    }

    //jump (2)
    for (i=1; i<=jr->sprites_nb_img[2]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 1/jump/right/image%d.png", i);
        jr->jump_r[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 1/jump/left/image%d.png", i);
        jr->jump_l[i-1] = IMG_Load(spname);
    }

    //attack (3)
    for (i=1; i<=jr->sprites_nb_img[3]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 1/attack/right/image%d.png", i);
        jr->attack_r[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 1/attack/left/image%d.png", i);
        jr->attack_l[i-1] = IMG_Load(spname);
    }
     
    //special attack(4)
        for (i=1; i<=jr->sprites_nb_img[4]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 1/sattack/right/image%d.png", i);
        jr->sattack_r[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 1/sattack/left/image%d.png", i);
        jr->sattack_l[i-1] = IMG_Load(spname);
    }

            //spown (5)
    for (i=1; i<=jr->sprites_nb_img[5]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 1/spown/right/image%d.png", i);
        jr->spown_r[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 1/spown/left/image%d.png", i);
        jr->spown_l[i-1] = IMG_Load(spname);
    }

        //hit (6)
        for (i=1; i<=jr->sprites_nb_img[6]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 1/hit/right/image%d.png", i);
        jr->hit_r[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 1/hit/left/image%d.png", i);
        jr->hit_l[i-1] = IMG_Load(spname);
    }

    //die (7)
    for (i=1; i<=jr->sprites_nb_img[7]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 1/die/right/image%d.png", i);
        jr->die_r[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 1/die/left/image%d.png", i);
        jr->die_l[i-1] = IMG_Load(spname);
    }
    //shield
    for (i=1; i<=jr->sprites_nb_img[8]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 1/shield/right/image%d.png", i);
        jr->shield_r[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 1/shield/left/image%d.png", i);
        jr->shield_l[i-1] = IMG_Load(spname);
    }
////////////////////////////////////////////////////////////////////////////////////new skin
        //idel (0)
    for (i=1; i<=jr->sprites_nb_img[0]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 2/idel/right/image%d.png", i);
        jr->idel_r2[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 2/idel/left/image%d.png", i);
        jr->idel_l2[i-1] = IMG_Load(spname);
    }

    //run (1)
    for (i=1; i<=jr->sprites_nb_img[1]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 2/run/right/image%d.png", i);
        jr->run_r2[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 2/run/left/image%d.png", i);
        jr->run_l2[i-1] = IMG_Load(spname);
    }

    //jump (2)
    for (i=1; i<=jr->sprites_nb_img[2]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 2/jump/right/image%d.png", i);
        jr->jump_r2[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 2/jump/left/image%d.png", i);
        jr->jump_l2[i-1] = IMG_Load(spname);
    }

    //attack (3)
    for (i=1; i<=jr->sprites_nb_img[3]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 2/attack/right/image%d.png", i);
        jr->attack_r2[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 2/attack/left/image%d.png", i);
        jr->attack_l2[i-1] = IMG_Load(spname);
    }
     
    //special attack(4)
        for (i=1; i<=jr->sprites_nb_img[4]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 2/sattack/right/image%d.png", i);
        jr->sattack_r2[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 2/sattack/left/image%d.png", i);
        jr->sattack_l2[i-1] = IMG_Load(spname);
    }

            //spown (5)
    for (i=1; i<=jr->sprites_nb_img[5]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 2/spown/right/image%d.png", i);
        jr->spown_r2[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 2/spown/left/image%d.png", i);
        jr->spown_l2[i-1] = IMG_Load(spname);
    }

        //hit (6)
        for (i=1; i<=jr->sprites_nb_img[6]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 2/hit/right/image%d.png", i);
        jr->hit_r2[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 2/hit/left/image%d.png", i);
        jr->hit_l2[i-1] = IMG_Load(spname);
    }

    //die (7)
    for (i=1; i<=jr->sprites_nb_img[7]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 2/die/right/image%d.png", i);
        jr->die_r2[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 2/die/left/image%d.png", i);
        jr->die_l2[i-1] = IMG_Load(spname);
    }







    ///init jr sounds
    int sndNB[9] = {1/*attack*/, 3/*dies*/, 4/*hited*/, 1/*jump*/, 2/*respown*/, 1/*special attack*/, 3/*spown*/, 1/*touch ground*/, 3/*walk*/ };//nb of tracks in each sprite sound
    
    jr->nbSounds = 9;//nb of sounds

    //seting the nb of sounds to the jr struct
    jr->Sound_nb_tracks = (int*) malloc(jr->nbSounds * sizeof(int));
    for (i=0; i<jr->nbSounds; i++){
        jr->Sound_nb_tracks[i] = sndNB[i];
    }

    //attack (0)
    for (i=1; i<=jr->Sound_nb_tracks[0]; i++ ){
        sprintf(spname, "assets/sound effects/player 1/attack/sound%d.wav", i);
        jr->attack_snd[i-1] = Mix_LoadWAV(spname);
    }

    //dies (1)
    for (i=1; i<=jr->Sound_nb_tracks[1]; i++ ){
        sprintf(spname, "assets/sound effects/player 1/dies/sound%d.wav", i);
        jr->dies_snd[i-1] = Mix_LoadWAV(spname);
    }

    //hited (2)
    for (i=1; i<=jr->Sound_nb_tracks[2]; i++ ){
        sprintf(spname, "assets/sound effects/player 1/got hit/sound%d.wav", i);
        jr->hited_snd[i-1] = Mix_LoadWAV(spname);
    }

    //jump (3)
    for (i=1; i<=jr->Sound_nb_tracks[3]; i++ ){
        sprintf(spname, "assets/sound effects/player 1/jump/sound%d.wav", i);
        jr->jump_snd[i-1] = Mix_LoadWAV(spname);
    }

    //respown (4)
    for (i=1; i<=jr->Sound_nb_tracks[4]; i++ ){
        sprintf(spname, "assets/sound effects/player 1/respown/sound%d.wav", i);
        jr->respown_snd[i-1] = Mix_LoadWAV(spname);
    }

    //special attack (5)
    for (i=1; i<=jr->Sound_nb_tracks[5]; i++ ){
        sprintf(spname, "assets/sound effects/player 1/special attack/sound%d.wav", i);
        jr->sp_attack_snd[i-1] = Mix_LoadWAV(spname);
    }

    //spown (6)
    for (i=1; i<=jr->Sound_nb_tracks[6]; i++ ){
        sprintf(spname, "assets/sound effects/player 1/spown/sound%d.wav", i);
        jr->spown_snd[i-1] = Mix_LoadWAV(spname);
    }

    //touch ground (7)
    for (i=1; i<=jr->Sound_nb_tracks[7]; i++ ){
        sprintf(spname, "assets/sound effects/player 1/touch ground/sound%d.wav", i);
        jr->touch_grnd_snd[i-1] = Mix_LoadWAV(spname);
    }

    //walk (8)
    for (i=1; i<=jr->Sound_nb_tracks[8]; i++ ){
        sprintf(spname, "assets/sound effects/player 1/walk/sound%d.wav", i);
        jr->walk_snd[i-1] = Mix_LoadWAV(spname);
    }


    jr->x = 0;
    jr->y = 350.0;
    jr->w = jr->idel_r[0]->w;
    jr->h = jr->idel_r[0]->h;
    jr->vit_mx = 300.0;
    jr->startspeed = 20;//20.0
    jr->vit_h = jr->startspeed;
    
    jr->vit_v = 0;
    jr->real_x = 0;
    jr->real_y = 0;
    //ground collision
    jr->inground = 0;
    jr->inwall = 0;

    jr->vit_x = 0;
    jr->vit_y = 0;

    jr->direction_x = 1;

    jr->stop = 0;

    jr->saut = 0;
    jr->presaut = 0;
    jr->saut_max = 200;//80
    jr->saut_vit = -100;

    jr->gravity = 20; //optional

    jr->state = 0;

    jr->keystates = SDL_GetKeyState(NULL);
    //player info
    jr->alive = 1;
    jr->dead = 0;
    jr->isdieng = 0;
    jr->lives = 2;
    jr->health = 50;
    jr->xp = 0;
    jr->hited = 0;
    jr->score = 0;
    
}

void AffJR(JR *jr, SDL_Surface *screen, int *nb_skin) {

    // Update jr animation
    if (SDL_GetTicks() >= jr->nextFrameTime) {
        jr->currentframe = (jr->currentframe + 1) % jr->sprites_nb_img[jr->state];//******
        jr->nextFrameTime = SDL_GetTicks() + jr->frameDelay;
    }


        // Draw jr sprite
        SDL_Rect jr_rect = { jr->x, jr->y, jr->w, jr->h };
        
        
        
        //draw score
         DrawScore(screen, jr->score); 
         jr->score += 1; //score update ever millisecond
         
        if(*nb_skin == 1){
        switch (jr->state){
        case 0://idel
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->idel_r[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->idel_l[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;
        
        case 1://run
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->run_r[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->run_l[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;

        case 2://jump
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->jump_r[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->jump_l[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;

        case 3://attack
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->attack_r[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                jr_rect.x = jr_rect.x - jr->attack_l[jr->currentframe]->w/2;
                SDL_BlitSurface(jr->attack_l[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;
        
        case 4://special attack
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->sattack_r[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                jr_rect.x = jr_rect.x - jr->sattack_l[jr->currentframe]->w/2;
                SDL_BlitSurface(jr->sattack_l[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;

            case 5://spown
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->spown_r[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->spown_l[jr->currentframe], NULL, screen, &jr_rect);
            }   
            break;   

            case 6://hit
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->hit_r[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->hit_l[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;     

            case 7://die
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->die_r[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->die_l[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;

            case 8://die
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->shield_r[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->shield_l[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;

                    


        }}
        if(*nb_skin == 2){
        switch (jr->state){
        case 0://idel
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->idel_r2[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->idel_l2[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;
        
        case 1://run
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->run_r2[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->run_l2[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;

        case 2://jump
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->jump_r2[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->jump_l2[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;

        case 3://attack
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->attack_r2[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                jr_rect.x = jr_rect.x - jr->attack_l2[jr->currentframe]->w/2;
                SDL_BlitSurface(jr->attack_l2[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;
        
        case 4://special attack
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->sattack_r2[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                jr_rect.x = jr_rect.x - jr->sattack_l2[jr->currentframe]->w/2;
                SDL_BlitSurface(jr->sattack_l2[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;

            case 5://spown
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->spown_r2[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->spown_l2[jr->currentframe], NULL, screen, &jr_rect);
            }   
            break;   

            case 6://hit
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->hit_r2[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->hit_l2[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;     

            case 7://die
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->die_r2[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->die_l2[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;
                    


        }


        }
    
    
    if (jr->state == 3 && jr->currentframe >= jr->sprites_nb_img[3]-1){
        jr->state = 0;
        jr->currentframe = 0;
    }
    if (jr->state == 4 && jr->currentframe >= jr->sprites_nb_img[4]-1){
        jr->state = 0; // Return to idle state after special attack animation finishes
        jr->currentframe = 0;
        // Perform special attack actions here
    }
    if (jr->state == 6 && jr->currentframe >= jr->sprites_nb_img[6]-1){
        jr->state = 0; // Return to idle state after hit animation finishes
        jr->currentframe = 0;
        // hit here
    }
        if (jr->state == 8 && jr->currentframe >= jr->sprites_nb_img[8]-1){
        jr->state = 0; // Return to idle state after hit animation finishes
        jr->currentframe = 0;
        // shield here
    }

}

void ConJR(JR *jr, SDL_Event event, int *quit, int *curren_screen){
    // Handle user input
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        *quit = 1;
                        break;
                    
                    case SDL_KEYDOWN:
                        
                        if (event.key.keysym.sym == jr->keys.attack){
                            if (jr->state != 3){
                                jr->currentframe = 0;
                                jrPlaySound(jr, "attack");
                                jr->state = 3;
                            }
                        }
                        if (event.key.keysym.sym == jr->keys.special){
                            if (jr->state != 4){
                                jr->currentframe = 0;
                                jrPlaySound(jr, "special attack");
                                jr->state = 4;
                            }
                        }

                             if (event.key.keysym.sym == jr->keys.shield){
                            if (jr->state != 8){
                                jr->currentframe = 0;
                                jr->state = 8;
                            }
                        }
                        if(event.key.keysym.sym == SDLK_g) {
                        
                            takeDamage(jr, 10); // Lose 10 health



                            }
                            if (jr->lives <= 0) {
                                jr->currentframe = 0;
                                
                                jrPlaySound(jr, "dies");
                                
                                *curren_screen = 4;
                                jr->health = 100;
                                jr->lives = 1;
                                }
                        

                        

                        if (event.key.keysym.sym == jr->keys.jump){
                            if (!jr->saut && jr->inground){
                                jr->presaut = jr->y;
                                jrPlaySound(jr, "jump");
                                jr->saut = 1;
                                jr->currentframe = 0;
                            }
                        }




                    break;
                }
            }

            //movment clicking
            if (jr->keystates[jr->keys.left]){
                if (jr->state != 1){
                    jr->direction_x = -1;
                    jr->vit_x = -1;
                    jrPlaySound(jr, "walk");
                    
                    jr->currentframe = 0;
                    jr->state = 1;
                }

                jr->vit_h = min(jr->vit_mx, jr->vit_h + 5);
            }
            else if (jr->keystates[jr->keys.right]){
                if (jr->state != 1){
                    jr->direction_x = 1;
                    jr->vit_x = 1;
                    jrPlaySound(jr, "walk");
                    jr->currentframe = 0;
                    jr->state = 1;
                }

                jr->vit_h = min(jr->vit_mx, jr->vit_h + 5);
            }
            else{
                if (jr->state != 4 && jr->state != 3 && jr->state != 6 && jr->state != 7 && jr->state != 8){
                    jr->vit_x = 0;

                    if (jr->state != 0){
                    jr->currentframe = 0;
                    jr->state = 0;
                }
                
                
                    jr->vit_h = 20;
                }
                
            }
            

            //jumping
            if (jr->vit_y == -1){
                jr->state = 2;
            }
            if (jr->vit_y == 1){
                jr->state = 2;
            }
}

void PlayerGetCollisionPoint(JR *player, SDL_Surface *ground_image){
        
    if ( (player->real_x + player->w >= 0 && player->real_x + player->w <= ground_image->w) && (player->real_y >= 0 && player->real_y <= ground_image->h) ){
        player->pp[0] = GetPixel(ground_image, (player->real_x + player->w), player->real_y);//0 none
    }

    if ( (player->real_x + player->w >= 0 && player->real_x + player->w <= ground_image->w) && (player->real_y >= 0 && player->real_y <= ground_image->h) ){
        player->pp[1] = GetPixel(ground_image, (player->real_x + player->w), player->real_y);//1 up-right
    }

    if ( (player->real_x + player->w/2 >= 0 && player->real_x + player->w/2 <= ground_image->w) && (player->real_y >= 0 && player->real_y <= ground_image->h) ){
        player->pp[2] = GetPixel(ground_image, player->w/2 + player->real_x, player->real_y);//2 up-center
    }

    if ( (player->real_x >= 0 && player->real_x <= ground_image->w) && (player->real_y >= 0 && player->real_y <= ground_image->h) ){
        player->pp[3] = GetPixel(ground_image, player->real_x, player->real_y);//3 up-left
    }

    if ( (player->real_x >= 0 && player->real_x <= ground_image->w) && (player->real_y + player->h/2 >= 0 && player->real_y + player->h/2 <= ground_image->h) ){
        player->pp[4] = GetPixel(ground_image, player->real_x, (player->real_y + player->h/2) );//4 center-left
    }

    if ( (player->real_x >= 0 && player->real_x <= ground_image->w) && (player->real_y + player->h >= 0 && player->real_y + player->h <= ground_image->h) ){
        player->pp[5] = GetPixel(ground_image, player->real_x, (player->real_y + player->h) );//5 bottom-left
    }

    if ( (player->real_x + player->w/2 >= 0 && player->real_x + player->w/2 <= ground_image->w) && (player->real_y + player->h >= 0 && player->real_y + player->h <= ground_image->h) ){
        player->pp[6] = GetPixel(ground_image, (player->real_x + player->w/2), (player->real_y + player->h) );//6 bottom-center
    }

    if ( (player->real_x + player->w >= 0 && player->real_x + player->w <= ground_image->w) && (player->real_y + player->h >= 0 && player->real_y + player->h <= ground_image->h) ){
        player->pp[7] = GetPixel(ground_image, (player->real_x + player->w), (player->real_y + player->h) );//7 bottom-right
    }

    if ( (player->real_x + player->w >= 0 && player->real_x + player->w <= ground_image->w) && (player->real_y + player->h/2 >= 0 && player->real_y + player->h/2 <= ground_image->h) ){
        player->pp[8] = GetPixel(ground_image, (player->real_x + player->w), (player->real_y + player->h/2) );//8 bottom-right
    }

    
}

void PlayerCollisionAndGravity(JR *player, float *delta_s, Level *lvl){///

    
    //inground vertical collision 
    if ( (( checkCollusion(player->pp[5], lvl->solid) || checkCollusion(player->pp[6], lvl->solid) || checkCollusion(player->pp[7], lvl->solid) )) && ( !checkCollusion(player->pp[4], lvl->solid) || (!checkCollusion(player->pp[8], lvl->solid)) ) && ( !checkCollusion(player->pp[1], lvl->solid) || (!checkCollusion(player->pp[3], lvl->solid)) ) )
    {
        if (player->inground != 1 ){
            player->firs_collusion_y = player->real_y - lvl->pos_y;
        }
        player->inground = 1;
    }
    else{
        player->inground = 0;
    }
    
    ///wall horizontal collision
    //left
    if( (checkCollusion(player->pp[3], lvl->solid) && checkCollusion(player->pp[4], lvl->solid)) || (checkCollusion(player->pp[4], lvl->solid) && checkCollusion(player->pp[5], lvl->solid)) || (checkCollusion(player->pp[3], lvl->solid) && checkCollusion(player->pp[5], lvl->solid)) )
    {
        player->inwall = -1;
    }

    //right
    else if( (checkCollusion(player->pp[1], lvl->solid) && checkCollusion(player->pp[8], lvl->solid)) || (checkCollusion(player->pp[7], lvl->solid) && checkCollusion(player->pp[8], lvl->solid)) || (checkCollusion(player->pp[1], lvl->solid) && checkCollusion(player->pp[7], lvl->solid)) )
    {
        player->inwall = 1;
    }

    else
    {
        player->inwall = 0;
    }

    if (player->y <= player->presaut - player->saut_max){
        player->saut = 0;
    }


    if (player->vit_x == -1 && player->inwall == -1)
    {
        player->vit_h = 0;
    }
    else if (player->vit_x == 1 && player->inwall == 1)
    {
        player->vit_h = 0;
    }
    if (player->y <= player->presaut - player->saut_max){
        player->saut = 0;
    }

    if (!player->inground){
        if (!player->saut){
            player->vit_v = 200;
            player->vit_y = 1;
        }
        if (player->saut){
            player->vit_v = player->saut_vit;
            player->vit_y = -1;
        }
    }
    if (player->inground){
        if (!player->saut){
            player->vit_v = 0;
            player->vit_y = 0;
        }
        if (player->saut){
            player->vit_v = player->saut_vit;
            player->vit_y = 1;
        }
    }
    ///movement

        //player y movement
        //printf("dely %f ---- jummping %d --- bj %d ------ yyy %d -- inground %d\n", *delta_s, player->isjumping, player->beforjumpy ,player->y, player->inground);
        
        //gravity
        player->y += player->vit_v * (*delta_s);
        
        if (player->inground && player->saut == 0 ){
            player->y += 0;
            player->y = (int) player->firs_collusion_y;

        }

           
        
        
        ///scrolling
        
        if (player->y >= SCREEN_H/5 && lvl->pos_y < (lvl->lvl1.bg->h - SCREEN_H) ){
            if (lvl->pos_y < (lvl->lvl1.bg->h - SCREEN_H/5)){
                player->y = SCREEN_H/5 + 1;
            }
            scrolling(lvl, "down", player->gravity * (*delta_s));
        }

        if (player->y < SCREEN_H/5 && lvl->pos_y > 0 ){
            scrolling(lvl, "up", player->gravity * (*delta_s));
        }
        
        

        //player x movement
        //left
        if (player->vit_x == -1 && player->inwall != -1){
            
            if (lvl->pos_x > 1 && player->x < SCREEN_W/2){
                scrolling(lvl, "left", -player->vit_h * (*delta_s));
                player->x -= player->vit_h* (*delta_s);
            }
            else{
                player->x -= player->vit_h* (*delta_s);
            }
        }
        
        if (player->vit_x == 1 && player->inwall != 1){
            if (player->x >= SCREEN_W/2 && lvl->pos_x < (lvl->lvl1.bg->w - (SCREEN_W)) ){
                scrolling(lvl, "right", player->vit_h* (*delta_s));
                player->x += player->vit_h* (*delta_s);
            }
            else {
                player->x += player->vit_h* (*delta_s);
            }
        }
        

  





 
        

        player->real_x = player->x + lvl->pos_x;
        player->real_y = player->y + lvl->pos_y;

        

        //printf("player x: %d ----- player y: %d ****** level y: %d -- level high: %d \n", player->real_x, player->real_y, lvl->pos_y, lvl->lvl1.bg->h);
        //printf("%d -- vs %f -- py %f\n",player->inground, player->vspeed, player->y);

}


void DrawScore(SDL_Surface *screen, int score) {
    // Load font
    TTF_Font *font = TTF_OpenFont("assets/fonts/ARCADECLASSIC.TTF", 24); // Load a font file  with size 24
    if (!font) {
        // Handle error
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return;
    }

    // Set text color
    SDL_Color textColor = {0, 0, 0}; // black color

    // Create surface from text
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score); // Format score as text
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText, textColor);

    // Set position for the score text
    SDL_Rect textRect = {520, 10, 0, 0}; // Top left corner

    // Blit text surface onto screen
    SDL_BlitSurface(textSurface, NULL, screen, &textRect);

    // Free surfaces and font
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

void jrPlaySound(JR *jr, char *sound_type){
    int cmp_nb = 0;
    int play_nb = 0;

    //attack (0)
    if (strcmp(sound_type, "attack") == 0){
        cmp_nb = jr->Sound_nb_tracks[0];
        play_nb = random_between(0, cmp_nb-1);
        Mix_PlayChannel(-1, jr->attack_snd[play_nb], 0);
    }

    //dies (1)
    if (strcmp(sound_type, "dies") == 0){
        cmp_nb = jr->Sound_nb_tracks[1];
        play_nb = random_between(0, cmp_nb-1);
        Mix_PlayChannel(-1, jr->dies_snd[play_nb], 0);
    }

    //hited (2)
    if (strcmp(sound_type, "hited") == 0){
        cmp_nb = jr->Sound_nb_tracks[2];
        play_nb = random_between(0, cmp_nb-1);
        Mix_PlayChannel(-1, jr->hited_snd[play_nb], 0);
    }

    //jump (3)
    if (strcmp(sound_type, "jump") == 0){
        cmp_nb = jr->Sound_nb_tracks[3];
        play_nb = random_between(0, cmp_nb-1);
        Mix_PlayChannel(-1, jr->jump_snd[play_nb], 0);
    }

    //respown (4)
    if (strcmp(sound_type, "respown") == 0){
        cmp_nb = jr->Sound_nb_tracks[4];
        play_nb = random_between(0, cmp_nb-1);
        Mix_PlayChannel(-1, jr->respown_snd[play_nb], 0);
    }

    //special attack (5)
    if (strcmp(sound_type, "special attack") == 0){
        cmp_nb = jr->Sound_nb_tracks[5];
        play_nb = random_between(0, cmp_nb-1);
        Mix_PlayChannel(-1, jr->sp_attack_snd[play_nb], 0);
    }

    //spown (6)
    if (strcmp(sound_type, "spown") == 0){
        cmp_nb = jr->Sound_nb_tracks[6];
        play_nb = random_between(0, cmp_nb-1);
        Mix_PlayChannel(-1, jr->spown_snd[play_nb], 0);
    }

    //touch ground (7)
    if (strcmp(sound_type, "touch ground") == 0){
        cmp_nb = jr->Sound_nb_tracks[7];
        play_nb = random_between(0, cmp_nb-1);
        Mix_PlayChannel(-1, jr->touch_grnd_snd[play_nb], 0);
    }

    //walk (8)
    if (strcmp(sound_type, "walk") == 0){
        cmp_nb = jr->Sound_nb_tracks[8];
        play_nb = random_between(0, cmp_nb-1);
        Mix_PlayChannel(-1, jr->walk_snd[play_nb], 0);
    }



}

void playerDeath(JR *jr, SDL_Surface *screen) {

  // Set up death animation timer
  int deathTimer = 0;
  int deathTimerMax = 1000; // 1 second

  // Set player state to dying
  jr->state = 7;

  // Reset animation
  jr->currentframe = 0; 

  // Play death sound
  jrPlaySound(jr, "dies");

  // Make player stop moving
  jr->vit_x = 0; 
  jr->vit_y = 0;

  // Reduce lives
  jr->lives--;

  // Check if game over
  if (jr->lives < 1) {
    // Trigger game over
  } else {
    // Respawn later
    jr->state = 6;
  }

  // Animate death frames over time
  while (deathTimer < deathTimerMax) {

    // Handle frame timing
    deathTimer++;
    if (deathTimer >= jr->frameDelay) {
      deathTimer = 0;

      // Increment frame
      jr->currentframe++;
      if (jr->currentframe >= jr->sprites_nb_img[7]) {
        jr->currentframe = jr->sprites_nb_img[7] - 1;
      }
    }

    // Draw current frame
   

  }

  // After animation finishes
  jr->dead = 1; 

}

// Call on lethal damage
//playerDeath(jr);



void takeDamage(JR *player, int damage) {
    SDL_Surface *screen;
  // Reduce health 
  player->health -= damage;

  // Check for no health
  if(player->health <= 0) {

    // Call death function
    playerDeath(player, screen);
    

  }
  else {

    // Play hurt sound 
    jrPlaySound(player, "hited");
    player->currentframe = 0; // Reset animation to first frame
    player->state = 6; // Set player to hurt state

    // Flash red 
    // ...

  }

  // Lose life if health drops below threshold
  if(player->health < 20) {
    player->lives--;
    player->health = 100; // Reset health
  }

}










