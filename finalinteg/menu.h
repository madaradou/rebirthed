#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include <string.h>
#include "structs.h"



typedef struct
{
    int musicVolume, sfxVolume;

    Mix_Music *mainMenuMusic;
    Mix_Chunk *btnHoverSndEffect, *btnClickSndEffect;
}Sounds;

typedef struct
{
    int x, y;
    int w, h;

    int img_nb;
    SDL_Surface** image;

    //sprite info
    int currentframe;
    int frameDelay;
    int nextFrameTime;
    

}Sprite;

typedef struct
{
    ///menu
    //bg
    Sprite menuMainBg;

    //btns
    Sprite mPlay_btn, mOption_btn, mQuit_btn;
    

    //slider
    Sprite mainMenuSlider;
    Sprite sldPlsBtn, sldMnsBtn;

    Sprite check_btn, closeBtn,pclose_Btn;
    Sprite newgame_Btn, loadgame_Btn, tic_Btn;
    Sprite resume_Btn, controls_Btn;
    Sprite  skin1_Btn, skin2_Btn;
    Sprite attack_Btn, special_Btn, jump_Btn, left_Btn, right_Btn;
    

}Sprites;


typedef struct
{
    Sprite spr;

    int x, y;
    int w, h;

    int alive;

    int state;

    char* btn_name;
    
}Button;

typedef struct
{
    Sprite spr;

    int x, y;
    int w, h;

    int state;

    int alive;

    char* slider_name;

    Button plusBtn, minsBtn;

}SliderBar;

typedef struct{
    Sprite bg;

    SliderBar musicSlider, sfxSlider;

    Button fullScreenCheckBtn, closeBtn;

}OptionsMenu;

typedef struct 
{
    Sprite bg;
    
    Button newgameBtn, loadgameBtn, closeBtn, ticBtn;
    



    
}PlayMenu;

typedef struct 
{
    Sprite bg;
    SDL_Color textColor;
    Button resumeBtn, controlsBtn, closeBtn;
    
}PauseMenu;

typedef struct 
{
    Sprite bg;
    SDL_Color textColor;
    Button skin1Btn, skin2Btn, closeBtn;
    
}SkinMenu;

typedef struct 
{
    Sprite bg;
    KeyConfig *keys;
    int selected;
    SDL_Color textColor;
    Button attackBtn, specialBtn, jumpBtn, leftBtn, rightBtn, closeBtn;
    
}ControlsMenu;



typedef struct
{
    Sprite bg;

    Button playBtn, optionsBtn, exitBtn;

    TTF_Font* font;
    SDL_Color textColor;
    SDL_Color textColor2;

    OptionsMenu options_menu;

    PlayMenu play_menu;

    PauseMenu pause_menu;

    SkinMenu skin_menu;

    ControlsMenu controls_menu;

    int getting_key_on;
    int pressed_key;
    Uint8 *keystate;



}MainMenu;







void initButton(Button *btn, char* btn_name, Sprite sprite, int x, int y);

void showButton(Button btn, SDL_Surface* screen);

void initSlider(SliderBar *sld_bar, char* slider_name, Sprite sprite, int x, int y, Sprites sprs);

void sliderUpdateVolume(Sounds *sounds, SliderBar *slider);

void sliderUpdateState(SliderBar *sld_bar, int action, Sounds *sounds);

void initMainMenu(MainMenu *menu, Sprites sprites);

void showMainMenu(MainMenu *menu, SDL_Surface* screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen);

int pointInRect(int x, int y, SDL_Rect rect);

int isMouseInsideButton(Button* button, int mouseX, int mouseY);

void controlMainMenu(MainMenu *menu, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen);

void drawText(SDL_Surface* screen, const char* text, int x, int y, TTF_Font* font, SDL_Color textColor);

void drawButonText(Button btn, SDL_Surface* screen, const char* text, TTF_Font* font, SDL_Color textColor);

void initOptionsMenu(MainMenu *menu, Sprites sprites);

void controlOptionsMenu(MainMenu *menu, SDL_Event *event, SDL_Surface* screen, Sounds sounds, int *quit, int *curren_screen);

void showOptionsMenu(MainMenu *menu, SDL_Surface* screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen);

void initPLayMenu(MainMenu *menu, Sprites sprites);

void controlPLayMenu(MainMenu *menu, SDL_Event *event, SDL_Surface* screen, Sounds sounds, int *quit, int *curren_screen);

void initMenu(MainMenu *main_menu, Sprites sprites);

void showMenu(MainMenu *main_menu, SDL_Surface* screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen, int *nb_skin, KeyConfig *keys);

void initSprite(Sprite* sprite, int imgCount, const char* folderPath);

void cleanupSprite(Sprite* sprite);

void showSprite(Sprite* sprite, SDL_Surface* screen, int x, int y);

void loadMenuSprites(Sprites *Sprites);

void loadAllSprites(Sprites *Sprites);

void cleanMenuSprites(Sprites *Sprites);

void CleanAllSprites(Sprites *Sprites);

void loadMusic(Mix_Music **msc, const char* soundPath);

void loadMenuSounds(Sounds *sounds);

void loadAllSounds(Sounds *sounds);

void playMusic(Mix_Music* msc);

void playSoundEffect(Mix_Chunk* soundEffect);

void setMusicVolume(Sounds *sounds, int volume);

void setSfxVolume(Sounds *sounds, int volume);

void initpauseMenu(MainMenu *menu, Sprites sprites);

void controlPauseMenu(MainMenu *menu, SDL_Event *event, SDL_Surface* screen, Sounds sounds, int *quit, int *curren_screen);

void showPauseMenu(MainMenu *menu, SDL_Surface *screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen);

void initskinMenu(MainMenu *menu, Sprites sprites);

void controlskinMenu(MainMenu *menu, SDL_Event *event, SDL_Surface* screen, Sounds sounds, int *quit, int *curren_screen, int *nb_skin);

void showSkinMenu(MainMenu *menu, SDL_Surface *screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen, int *nb_skin);

void initcontrolsMenu(MainMenu *menu, Sprites sprites);

void controlsControlsMenu(MainMenu *menu, SDL_Event *event, SDL_Surface* screen, Sounds sounds, int *quit, int *curren_screen, KeyConfig *keys);

void showControls(MainMenu *menu, SDL_Surface *screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen, KeyConfig *keys);


#endif // MENU_H
