#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct {
  int left;
  int right; 
  int jump;
  int attack;
  int special;
  int shield;
} KeyConfig;

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
    SDL_Surface *idel_r[20], *run_r[20], *jump_r[3], *attack_r[9], *sattack_r[6], *die_r[10], *spown_r[4], *hit_r[3], *shield_r[8], *dash_r[10];
    SDL_Surface *idel_l[20], *run_l[20], *jump_l[3], *attack_l[9], *sattack_l[6], *die_l[10], *spown_l[4], *hit_l[3], *shield_l[8], *dash_l[10];
    
    SDL_Surface *idel_r2[20], *run_r2[20], *jump_r2[3], *attack_r2[9], *sattack_r2[6], *die_r2[10], *spown_r2[4], *hit_r2[3], *dash_r2[10];
    SDL_Surface *idel_l2[20], *run_l2[20], *jump_l2[3], *attack_l2[9], *sattack_l2[6], *die_l2[10], *spown_l2[4], *hit_l2[3], *dash_l2[10];

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
    int height;

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
    

    //jumping
    int saut;
    int presaut;
    int saut_max;
    int saut_vit;

    //garvity
    int gravity;

    //controller
    Uint8* keystates;
    KeyConfig keys;
    //new
    
    


    //score
    int score;

     //sound effects
    int nbSounds;
    int *Sound_nb_tracks;
    Mix_Chunk *attack_snd[1], *dies_snd[3], *hited_snd[4], *jump_snd[3], *respown_snd[3], *sp_attack_snd[1], *spown_snd[3], *touch_grnd_snd[3], *walk_snd[3];


} JR;

typedef struct {
    int x, y;
    int w, h;

    //player bars gui
    int nbStuff;
    int *sprites_nb_img;
    int currentImgInd;

    //player health bar;
    SDL_Surface *player_health_bar[11];

    //player hearts
    SDL_Surface *player_hearts[2];
    int max_hearts;
    int heart_x, heart_y;
    int heart_w, heart_h;

    //face icons
    int face_icon_x, face_icon_y;
    int face_icon_w, face_icon_h;
    SDL_Surface *player_face_icon[11];



}GameGUI;





#endif //STRUCTS_INCLUDED


