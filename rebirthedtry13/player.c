
#include "player.h"
#include "assets.h"


double min(double a, double b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int random_between(int min, int max) {
    srand(time(NULL));
    int random_num = rand();
    random_num = (random_num % (max - min + 1)) + min;
    return random_num;
}


void InitJR(JR *jr){
    int i;

    //init jr moves
    int spNB[10] = {8/*idel*/, 8/*run*/, 3/*jump*/, 8/*attack*/, 6/*sattack*/, 10/*die*/, 4/*spown*/, 3/*hit*/, 8/*shield*/, 9/*dash*/};//nb of images in each sprite move
    
    jr->nbMoves = 10;//nb of moves

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

            //dash (7)
    for (i=1; i<=jr->sprites_nb_img[9]; i++ ){
        //right
        sprintf(spname, "assets/sprites/player 1/dash/right/image%d.png", i);
        jr->dash_r[i-1] = IMG_Load(spname);

        //left
        sprintf(spname, "assets/sprites/player 1/dash/left/image%d.png", i);
        jr->dash_l[i-1] = IMG_Load(spname);
    }
////////////////////////////////////////////////////////////////////////////////////new skin








    ///init jr sounds
    int sndNB[10] = {1/*attack*/, 3/*dies*/, 4/*hited*/, 1/*jump*/, 2/*respown*/, 1/*special attack*/, 3/*spown*/, 1/*touch ground*/, 3/*walk*/, 6/*dash*/ };//nb of tracks in each sprite sound
    
    jr->nbSounds = 10;//nb of sounds

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
    jr->y = 360;
    jr->w = jr->idel_r[0]->w;
    jr->h = jr->idel_r[0]->h;
    jr->vit_mx = 300.0;
    jr->vit_h = 20;
    jr->vit_v = 0;

    jr->vit_x = 0;
    jr->vit_y = 0;

    jr->direction_x = 1;

    jr->stop = 0;

    jr->saut = 0;
    jr->presaut = 0;
    jr->saut_max = 80;
    jr->saut_vit = -100;

    jr->gravity = 200; //optional

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
    jr->height = 45;
    
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

             case 9://dash
            if (jr->direction_x == 1){
                SDL_BlitSurface(jr->dash_r[jr->currentframe], NULL, screen, &jr_rect);
            }
            if (jr->direction_x == -1){
                SDL_BlitSurface(jr->dash_l[jr->currentframe], NULL, screen, &jr_rect);
            }
            break;


                    


        }}
        

      
                    


        

        
    
    
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
      if (jr->state == 9 && jr->currentframe >= jr->sprites_nb_img[9]-1){
        jr->state = 0;
        jr->currentframe = 0;
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
                        
                            takeDamage(jr, 10); 



                            }
                            if (jr->lives <= 0) {
                                jr->currentframe = 0;
                                
                                jrPlaySound(jr, "dies");
                                
                                *curren_screen = 4;
                                }

                            if (event.key.keysym.sym == SDLK_a){
                            if (jr->state != 9){
                                jr->currentframe = 0;
                               jr->state = 9;
                                
                            }
                        }
                        

                        

                        if (event.key.keysym.sym == jr->keys.jump){
                            if (!jr->saut && jr->stop){
                                jr->presaut = jr->y;
                                jrPlaySound(jr, "jump");
                                jr->saut = 1;
                                jr->currentframe = 0;
                            }
                        }




                    break;
                }
            }
            if (event.key.keysym.sym == SDLK_o){
                *curren_screen = 4;

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
                if (jr->state != 4 && jr->state != 3 && jr->state != 6 && jr->state != 7 && jr->state != 8 && jr->state != 9){
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




void MoveJR(JR *jr){
    
   if (jr->y >= 370) {
        jr->stop = 1;
    } else {
        jr->stop = 0;
    }

    if (jr->y <= jr->presaut - jr->saut_max){
        jr->saut = 0;
    }

    if (!jr->stop){
        if (!jr->saut){
            jr->vit_v = 200;
            jr->vit_y = 1;
        }
        if (jr->saut){
            jr->vit_v = jr->saut_vit;
            jr->vit_y = -1;
        }
    }
    if (jr->stop){
        if (!jr->saut){
            jr->vit_v = 0;
            jr->vit_y = 0;
        }
        if (jr->saut){
            jr->vit_v = jr->saut_vit;
            jr->vit_y = 1;
        }
    }

    ///movement
    float speedFactor = 0.012;

    //jr y movement
    
    jr->y += jr->vit_v *speedFactor ;

    //jr x movement
    if (jr->vit_x == -1){
        jr->x -= jr->vit_h *speedFactor;
    }
    if (jr->vit_x == 1){
        jr->x += jr->vit_h *speedFactor;
    }
}







void DrawScore(SDL_Surface *screen, int score) {
    
    TTF_Font *font = TTF_OpenFont("assets/fonts/ARCADECLASSIC.TTF", 24); // Load a font file  with size 24
    if (!font) {
       
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return;
    }

 
    SDL_Color textColor = {0, 0, 0}; // black color

  
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score); // Format score as text
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText, textColor);


    SDL_Rect textRect = {520, 10, 0, 0}; // Top left corner

    
    SDL_BlitSurface(textSurface, NULL, screen, &textRect);

   
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




void takeDamage(JR *player, int damage) {
    SDL_Surface *screen;
  // Reduce health 
  player->health -= damage;

  // Check for no health
  if(player->health <= 0) {


    

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










