#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

typedef struct {
    SDL_Surface *img_bg; 
    SDL_Rect position_bg1, position_bg2; // Positions for both halves of the background
    SDL_Rect camera1, camera2; // Cameras for both halves of the background
    int speed;    
    int frame;    
    SDL_Surface *imgg[10];
} background;




typedef struct 
{
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



/*
typedef struct
{
    SDL_Surface *texte1;
    SDL_Surface *num;
    char number[20];
    char texte[20];
    SDL_Rect position_texte;
    SDL_Rect position_number;  
    TTF_Font *police;
    int valeur_score;
}
score ;
typedef struct{
    int score;
    int temps;
    char playerName[20];
    SDL_Surface *surfaceScore;
    SDL_Surface *surfaceTemps;
    SDL_Surface *surfaceName;
    SDL_Rect positionScore;
    SDL_Rect positionTemps;
    SDL_Rect positionName;
    TTF_Font *police;
} ScoreInfo;
*/


int random_between(int min, int max);


///////////////////background////////////////////////
void initialiser_background(background *bg ,SDL_Surface *ecran,int i);
void afficher_background(background bg, SDL_Surface * ecran);
void scrolling_bg(int direction,background *bg);


///////////////////////////animation//////////////////////////
void initefeu(background *b,int i);
void afficheranim(background b,SDL_Surface *screen);
void animerBack (background* b);
void free_anim(background *b);

///////////////////////////son/////////////////////////////
void initialiser_audio(Mix_Music *music);
void liberer_musique (Mix_Music *music);

void init_sound_player(JR *jr);
void jrPlaySound(JR *jr, char *sound_type);
void controlSounds(SDL_Event event , int *quit, JR *jr);
 

//////////////////////meilleur score///////////////////
/*void saveScore(ScoreInfo s, char *fileName);
void bestScore(char *filename, ScoreInfo trois[]);
void afficherBest(SDL_Surface *ecran, ScoreInfo t[]);
*/
#endif 

 
 
 