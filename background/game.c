
#include "game.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <stdlib.h>
#include <time.h>

int random_between(int min, int max) {
    srand(time(NULL));
    int random_num = rand();
    random_num = (random_num % (max - min + 1)) + min;
    return random_num;
}

/////////////////////////// Background ///////////////////////////

void initialiser_background(background *bg, SDL_Surface *ecran,int i) {
    if (!i) {
        bg->position_bg1.x = 0; // Set the x-coordinate of the first background
        bg->position_bg1.y = 0; // Set the y-coordinate of the first background
        bg->position_bg2.x = 0; // Set the x-coordinate of the second background
        bg->position_bg2.y = SCREEN_HEIGHT / 2; // Set the y-coordinate of the second background
    } else {
        bg->position_bg1.x = 0; // Set the x-coordinate of the first background
        bg->position_bg1.y = SCREEN_HEIGHT / 2; // Set the y-coordinate of the first background
        bg->position_bg2.x = 0; // Set the x-coordinate of the second background
        bg->position_bg2.y = 0; // Set the y-coordinate of the second background
    }

    // Set the width and height of both backgrounds to match the screen
    bg->position_bg1.w = SCREEN_WIDTH;
    bg->position_bg1.h = SCREEN_HEIGHT / 2;
    bg->position_bg2.w = SCREEN_WIDTH;
    bg->position_bg2.h = SCREEN_HEIGHT / 2;

    // Set other properties as before
    bg->speed = 5;

    // Load the background image
    bg->img_bg = IMG_Load("images/fadda kbira.png");
    if (bg->img_bg == NULL) {
        printf("Failed to load background image: %s\n", IMG_GetError());
        // Handle error appropriately
    }
}


void afficher_background(background bg, SDL_Surface *ecran) {
    // Clear the entire screen
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    // Blit the background images onto the screen
    SDL_BlitSurface(bg.img_bg, NULL, ecran, &bg.position_bg1);
    SDL_BlitSurface(bg.img_bg, NULL, ecran, &bg.position_bg2);

    // Update the display
    SDL_Flip(ecran);
}


void scrolling_bg(int direction, background *bg) {
    switch (direction) {
        case 1: // Scroll left
            bg->position_bg1.x -= bg->speed;
            bg->position_bg2.x -= bg->speed;
            if (bg->position_bg1.x <= -SCREEN_WIDTH)
                bg->position_bg1.x = SCREEN_WIDTH - 5;
            if (bg->position_bg2.x <= -SCREEN_WIDTH)
                bg->position_bg2.x = SCREEN_WIDTH - 5;
            break;
        case 2: // Scroll right
            bg->position_bg1.x += bg->speed;
            bg->position_bg2.x += bg->speed;
            if (bg->position_bg1.x >= SCREEN_WIDTH)
                bg->position_bg1.x = 0;
            if (bg->position_bg2.x >= SCREEN_WIDTH)
                bg->position_bg2.x = 0;
            break;
        case 3: // Scroll up
            bg->position_bg1.y -= bg->speed;
            bg->position_bg2.y -= bg->speed;
            if (bg->position_bg1.y <= -SCREEN_HEIGHT)
                bg->position_bg1.y = SCREEN_HEIGHT - 5;
            if (bg->position_bg2.y <= -SCREEN_HEIGHT)
                bg->position_bg2.y = SCREEN_HEIGHT - 5;
            break;
        case 4: // Scroll down
            bg->position_bg1.y += bg->speed;
            bg->position_bg2.y += bg->speed;
            if (bg->position_bg1.y >= SCREEN_HEIGHT)
                bg->position_bg1.y = 0;
            if (bg->position_bg2.y >= SCREEN_HEIGHT)
                bg->position_bg2.y = 0;
            break;
        default:
            break;
    }
}

/////////////////////////// Sound ///////////////////////////

void initialiser_audio(Mix_Music *music) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        printf("%s", SDL_GetError());
    }

    music = Mix_LoadMUS("assets/sounds/son .mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME);
}

void liberer_musique(Mix_Music *music) {
    Mix_FreeMusic(music);
}

/////////////////////////// Animation ///////////////////////////

void initefeu(background *bg, int i) {
    bg->imgg[0] = IMG_Load("images/b01.png");
    bg->imgg[1] = IMG_Load("images/b02.png");
    bg->imgg[2] = IMG_Load("images/b03.png");
    bg->imgg[3] = IMG_Load("images/b04.png");
    bg->imgg[4] = IMG_Load("images/b05.png");
    bg->imgg[5] = IMG_Load("images/b06.png");
    bg->imgg[6] = IMG_Load("images/b07.png");
    bg->imgg[7] = IMG_Load("images/b08.png");
    bg->imgg[8] = IMG_Load("images/b09.png");
    bg->imgg[9] = IMG_Load("images/b010.png");

    bg->position_bg1.x = 100;
    if (!i)
        bg->position_bg1.y = 100;
    else
        bg->position_bg1.y = 400;

    bg->frame = 0;
}

void afficheranim(background bg, SDL_Surface *ecran) {
    SDL_BlitSurface(bg.imgg[bg.frame], NULL, ecran, &bg.position_bg1);
}

void free_anim(background *bg) {
    for (int i = 0; i < 10; i++) {
        SDL_FreeSurface(bg->imgg[i]);
    }
}

void animerBack(background *bg) {
    if (bg->frame == 9) {
        bg->frame = 0;
    } else {
        (bg->frame)++;
    }
}

/////////////////////////// Sound Effects ///////////////////////////

void init_sound_player(JR *jr) {
    char spname[256];
    int i;
    ///init jr sounds
    int sndNB[9] = {1 /*attack*/, 3 /*dies*/, 4 /*hited*/, 1 /*jump*/, 2 /*respown*/, 1 /*special attack*/, 3 /*spown*/, 1 /*touch ground*/, 3 /*walk*/}; // nb of tracks in each sprite sound

    jr->nbSounds = 9; // nb of sounds

    // setting the nb of sounds to the jr struct
    jr->Sound_nb_tracks = (int *)malloc(jr->nbSounds * sizeof(int));
    for (i = 0; i < jr->nbSounds; i++) {
        jr->Sound_nb_tracks[i] = sndNB[i];
    }

    // Adjust file paths to fit your directory structure
    // (I'm assuming the original directory structure here)
    // Modify accordingly if the structure is different

    // attack (0)
    for (i = 1; i <= jr->Sound_nb_tracks[0]; i++) {
        sprintf(spname, "assets/sound effects/player 1/attack/sound%d.wav", i);
        jr->attack_snd[i - 1] = Mix_LoadWAV(spname);
    }

    // dies (1)
    for (i = 1; i <= jr->Sound_nb_tracks[1]; i++) {
        sprintf(spname, "assets/sound effects/player 1/dies/sound%d.wav", i);
        jr->dies_snd[i - 1] = Mix_LoadWAV(spname);
    }

    // hited (2)
    for (i = 1; i <= jr->Sound_nb_tracks[2]; i++) {
        sprintf(spname, "assets/sound effects/player 1/got hit/sound%d.wav", i);
        jr->hited_snd[i - 1] = Mix_LoadWAV(spname);
    }

    // jump (3)
    for (i = 1; i <= jr->Sound_nb_tracks[3]; i++) {
        sprintf(spname, "assets/sound effects/player 1/jump/sound%d.wav", i);
        jr->jump_snd[i - 1] = Mix_LoadWAV(spname);
    }

    // respown (4)
    for (i = 1; i <= jr->Sound_nb_tracks[4]; i++) {
        sprintf(spname, "assets/sound effects/player 1/respown/sound%d.wav", i);
        jr->respown_snd[i - 1] = Mix_LoadWAV(spname);
    }

    // special attack (5)
    for (i = 1; i <= jr->Sound_nb_tracks[5]; i++) {
        sprintf(spname, "assets/sound effects/player 1/special attack/sound%d.wav", i);
        jr->sp_attack_snd[i - 1] = Mix_LoadWAV(spname);
    }

    // spown (6)
    for (i = 1; i <= jr->Sound_nb_tracks[6]; i++) {
        sprintf(spname, "assets/sound effects/player 1/spown/sound%d.wav", i);
        jr->spown_snd[i - 1] = Mix_LoadWAV(spname);
    }

    // touch ground (7)
    for (i = 1; i <= jr->Sound_nb_tracks[7]; i++) {
        sprintf(spname, "assets/sound effects/player 1/touch ground/sound%d.wav", i);
        jr->touch_grnd_snd[i - 1] = Mix_LoadWAV(spname);
    }

    // walk (8)
    for (i = 1; i <= jr->Sound_nb_tracks[8]; i++) {
        sprintf(spname, "assets/sound effects/player 1/walk/sound%d.wav", i);
        jr->walk_snd[i - 1] = Mix_LoadWAV(spname);
    }
}

void jrPlaySound(JR *jr, char *sound_type) {
    int cmp_nb = 0;
    int play_nb = 0;

    // attack (0)
    if (strcmp(sound_type, "attack") == 0) {
        cmp_nb = jr->Sound_nb_tracks[0];
        play_nb = random_between(0, cmp_nb - 1);
        Mix_PlayChannel(-1, jr->attack_snd[play_nb], 0);
    }

    // dies (1)
    if (strcmp(sound_type, "dies") == 0) {
        cmp_nb = jr->Sound_nb_tracks[1];
        play_nb = random_between(0, cmp_nb - 1);
        Mix_PlayChannel(-1, jr->dies_snd[play_nb], 0);
    }

    // hited (2)
    if (strcmp(sound_type, "hited") == 0) {
        cmp_nb = jr->Sound_nb_tracks[2];
        play_nb = random_between(0, cmp_nb - 1);
        Mix_PlayChannel(-1, jr->hited_snd[play_nb], 0);
    }

    // jump (3)
    if (strcmp(sound_type, "jump") == 0) {
        cmp_nb = jr->Sound_nb_tracks[3];
        play_nb = random_between(0, cmp_nb - 1);
        Mix_PlayChannel(-1, jr->jump_snd[play_nb], 0);
    }

    // respown (4)
    if (strcmp(sound_type, "respown") == 0) {
        cmp_nb = jr->Sound_nb_tracks[4];
        play_nb = random_between(0, cmp_nb - 1);
        Mix_PlayChannel(-1, jr->respown_snd[play_nb], 0);
    }

    // special attack (5)
    if (strcmp(sound_type, "special attack") == 0) {
        cmp_nb = jr->Sound_nb_tracks[5];
        play_nb = random_between(0, cmp_nb - 1);
        Mix_PlayChannel(-1, jr->sp_attack_snd[play_nb], 0);
    }

    // spown (6)
    if (strcmp(sound_type, "spown") == 0) {
        cmp_nb = jr->Sound_nb_tracks[6];
        play_nb = random_between(0, cmp_nb - 1);
        Mix_PlayChannel(-1, jr->spown_snd[play_nb], 0);
    }

    // touch ground (7)
    if (strcmp(sound_type, "touch ground") == 0) {
        cmp_nb = jr->Sound_nb_tracks[7];
        play_nb = random_between(0, cmp_nb - 1);
        Mix_PlayChannel(-1, jr->touch_grnd_snd[play_nb], 0);
    }

    // walk (8)
    if (strcmp(sound_type, "walk") == 0) {
        cmp_nb = jr->Sound_nb_tracks[8];
        play_nb = random_between(0, cmp_nb - 1);
        Mix_PlayChannel(-1, jr->walk_snd[play_nb], 0);
    }
}

void controlSounds(SDL_Event event, int *quit, JR *jr) {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *quit = 1;
                break;

            case SDL_KEYDOWN:

                if (event.key.keysym.sym == SDLK_a) {
                    jrPlaySound(jr, "attack");
                }
                if (event.key.keysym.sym == SDLK_d) {
                    jrPlaySound(jr, "dies");
                }
                if (event.key.keysym.sym == SDLK_h) {
                    jrPlaySound(jr, "hited");
                }
                if (event.key.keysym.sym == SDLK_j) {
                    jrPlaySound(jr, "jump");
                }
                if (event.key.keysym.sym == SDLK_r) {
                    jrPlaySound(jr, "respown");
                }
                if (event.key.keysym.sym == SDLK_q) {
                    jrPlaySound(jr, "special attack");
                }
                if (event.key.keysym.sym == SDLK_s) {
                    jrPlaySound(jr, "spown");
                }
                if (event.key.keysym.sym == SDLK_t) {
                    jrPlaySound(jr, "touch ground");
                }
                if (event.key.keysym.sym == SDLK_w) {
                    jrPlaySound(jr, "walk");
                }

                break;
        }
    }
}