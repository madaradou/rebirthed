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
int random_between(int min, int max) {
    srand(time(NULL));
    int random_num = rand();
    random_num = (random_num % (max - min + 1)) + min;
    return random_num;
}
typedef struct {
    int x, y; //player pos
    int w, h; //player h && w

    //sprite info
    int currentframe;
    int frameDelay;
    int nextFrameTime;
    
    //player moves
    int nbMoves;
    int *sprites_nb_img;
    SDL_Surface *idel_r[20], *run_r[20], *jump_r[3], *attack_r[9], *sattack_r[6], *die_r[10], *spown_r[4], *hit_r[3];
    SDL_Surface *idel_l[20], *run_l[20], *jump_l[3], *attack_l[9], *sattack_l[6], *die_l[10], *spown_l[4], *hit_l[3];;
    
    SDL_Surface *idel_r2[20], *run_r2[20], *jump_r2[3], *attack_r2[9], *sattack_r2[6], *die_r2[10], *spown_r2[4], *hit_r2[3];
    SDL_Surface *idel_l2[20], *run_l2[20], *jump_l2[3], *attack_l2[9], *sattack_l2[6], *die_l2[10], *spown_l2[4], *hit_l2[3];;

    //player info
    int first_apperance;
    int alive;
    int dead;
    int isdieng;
    int state;
    int hited;
    int attack_end;
    int lives;
    int health;
    int xp;

    //direction
    int direction_x;

    //speed check
    int vit_x;
    int vit_y;

    //speed var
    float vit_h;
    float vit_v;
    float vit_mx;

    //ground collision
    int stop;
    SDL_Color pp[9];

    //jumping
    int saut;
    int presaut;
    int saut_max;
    int saut_vit;

    //garvity
    int gravity;

    //controller
    Uint8* keystates;
    //new
    
    


    //score
    int score;

     //sound effects
    int nbSounds;
    int *Sound_nb_tracks;
    Mix_Chunk *attack_snd[1], *dies_snd[3], *hited_snd[4], *jump_snd[3], *respown_snd[3], *sp_attack_snd[1], *spown_snd[3], *touch_grnd_snd[3], *walk_snd[3];


} JR;
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