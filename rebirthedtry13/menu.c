#include "menu.h"
#include "assets.h"

void loadMusic(Mix_Music** msc, const char* soundPath){
    *msc = Mix_LoadMUS(soundPath);
    if (*msc == NULL) {
        fprintf(stderr, "Could not load music! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }
}

void loadSoundEffect(Mix_Chunk** soundEffect, const char* filePath) {
    *soundEffect = Mix_LoadWAV(filePath);
    if (*soundEffect == NULL) {
        fprintf(stderr, "Could not load sound effect from '%s'! SDL_mixer Error: %s\n", filePath, Mix_GetError());
    }
}

void playMusic(Mix_Music* msc){
    Mix_PlayMusic(msc, -1);
}

void playSoundEffect(Mix_Chunk* soundEffect){
    Mix_PlayChannel(-1, soundEffect, 0);
}

void setMusicVolume(Sounds *sounds, int volume) {
    sounds->musicVolume = volume;
    Mix_VolumeMusic(sounds->musicVolume);
}

void setSfxVolume(Sounds *sounds, int volume) {
    sounds->sfxVolume = volume;
    Mix_Volume(-1, sounds->sfxVolume);  // -1 sets the volume for all channels
}

void loadMenuSounds(Sounds *sounds){
    loadMusic(&sounds->mainMenuMusic, "./assets/sounds/music/menu/backroundanimatedmusic.mp3");

    loadSoundEffect(&sounds->btnHoverSndEffect, "./assets/sounds/sound effects/menu/sekiro hoversound.wav");
    loadSoundEffect(&sounds->btnClickSndEffect, "./assets/sounds/sound effects/menu/btn click.wav");
    loadSoundEffect(&sounds->pausesndeffect, "assets/sounds/sound effects/menu/YOU DIED (HD).wav");
}

void loadAllSounds(Sounds *sounds){
    setMusicVolume(sounds, 128);
    setSfxVolume(sounds, 128);

    loadMenuSounds(sounds);
}

void initSprite(Sprite* sprite, int imgCount, const char* folderPath) {
    sprite->x = 0;
    sprite->y = 0;
    
    sprite->img_nb = imgCount;

    // Allocate memory for the image array
    sprite->image = (SDL_Surface**)malloc(imgCount * sizeof(SDL_Surface*));
    if (sprite->image == NULL) {
        fprintf(stderr, "Failed to allocate memory for image array\n");
        exit(1); // or handle the error appropriately
    }

    // Initialize each element in the image array to NULL
    for (int i = 0; i < imgCount; ++i) {
        sprite->image[i] = NULL;
    }

    // Load images from the specified folder
    for (int i = 0; i < imgCount; ++i) {
        char imagePath[256];
        sprintf(imagePath, "%s/image%d.png", folderPath, i+1);
        sprite->image[i] = IMG_Load(imagePath);

        if (sprite->image[i] == NULL) {
            fprintf(stderr, "Could not load sprite image %d from folder %s! SDL_image Error: %s\n", i, folderPath, IMG_GetError());
        }
    }

    if (sprite->image[0] != NULL){
        sprite->w = sprite->image[0]->w;
        sprite->h = sprite->image[0]->h;
    }
    else{
        sprite->w = 0;
        sprite->h = 0;
    }

    //sprite animation
    sprite->currentframe = 0;
    sprite->frameDelay = 700;
    sprite->nextFrameTime = 0;

}

//high
void initSpriteHigh(Sprite* sprite, int imgCount, const char* folderPath, int fd) {
    sprite->x = 0;
    sprite->y = 0;
    
    sprite->img_nb = imgCount;

    // Allocate memory for the image array
    sprite->image = (SDL_Surface**)malloc(imgCount * sizeof(SDL_Surface*));
    if (sprite->image == NULL) {
        fprintf(stderr, "Failed to allocate memory for image array\n");
        exit(1); // or handle the error appropriately
    }

    // Initialize each element in the image array to NULL
    for (int i = 0; i < imgCount; ++i) {
        sprite->image[i] = NULL;
    }

    // Load images from the specified folder
    for (int i = 0; i < imgCount; ++i) {
        char imagePath[256];
        sprintf(imagePath, "%s/image%d.png", folderPath, i+1);
        sprite->image[i] = IMG_Load(imagePath);

        if (sprite->image[i] == NULL) {
            fprintf(stderr, "Could not load sprite image %d from folder %s! SDL_image Error: %s\n", i, folderPath, IMG_GetError());
        }
    }

    if (sprite->image[0] != NULL){
        sprite->w = sprite->image[0]->w;
        sprite->h = sprite->image[0]->h;
    }
    else{
        sprite->w = 0;
        sprite->h = 0;
    }

    //sprite animation
    sprite->currentframe = 0;
    sprite->frameDelay = fd;
    sprite->nextFrameTime = 0;

}

void cleanupSprite(Sprite* sprite) {
    // Free each SDL_Surface in the image array
    for (int i = 0; i < sprite->img_nb; ++i) {
        SDL_FreeSurface(sprite->image[i]);
    }

    // Free the image array
    free(sprite->image);
}

void showSprite(Sprite* sprite, SDL_Surface* screen, int x, int y) {
    // Update menu animation
    if (SDL_GetTicks() >= sprite->nextFrameTime){
        sprite->currentframe = (sprite->currentframe + 1) % sprite->img_nb;
        sprite->nextFrameTime = SDL_GetTicks() + sprite->frameDelay;
    }

    // Set the position of the image
    SDL_Rect destinationRect = {x, y, 0, 0};

    // Blit the current image onto the screen at the specified position
    SDL_BlitSurface(sprite->image[sprite->currentframe], NULL, screen, &destinationRect);
    
}

void loadMenuSprites(Sprites *Sprites){
    
    //bg
    initSpriteHigh(&Sprites->menuMainBg, 2, "./assets/backrounds/menu/main", 900);

    initSprite(&Sprites->menuplaybg, 1, "assets/backrounds/menu/play");

    initSprite(&Sprites->menuoptionbg, 1, "assets/backrounds/menu/options");

    initSpriteHigh(&Sprites->pausebg, 60, "assets/backrounds/menu/pause", 100);




    
    //btnplay
    initSprite(&Sprites->mPlay_btn, 3, "./assets/sprites/menu/buttons/mplay_btn");

    //btnoption
    initSprite(&Sprites->mOption_btn, 3, "./assets/sprites/menu/buttons/moption_btn");

    //quitbtn
    initSprite(&Sprites->mQuit_btn, 3, "./assets/sprites/menu/buttons/mquit_btn");
    //play close button
    initSprite(&Sprites->pclose_Btn, 3, "./assets/sprites/menu/buttons/pclose_btn");

    //new game button
    initSprite(&Sprites->newgame_Btn, 3, "./assets/sprites/menu/buttons/pnewgame_btn");

    //load game button
    initSprite(&Sprites->loadgame_Btn, 3, "./assets/sprites/menu/buttons/ploadgame_btn");
    //resume button
    initSprite(&Sprites->resume_Btn, 3, "./assets/sprites/menu/buttons/resume_btn");
    //controls button
    initSprite(&Sprites->controls_Btn, 3, "./assets/sprites/menu/buttons/controls_btn");
    //skin1 Button
    initSprite(&Sprites->skin1_Btn, 3, "assets/sprites/menu/buttons/skin1_btn");
    //skin2 Button
    initSprite(&Sprites->skin2_Btn, 3, "assets/sprites/menu/buttons/skin2_btn");
    //attack button
    initSprite(&Sprites->attack_Btn, 3, "assets/sprites/menu/buttons/attack_btn");
    //special button
    initSprite(&Sprites->special_Btn, 3, "assets/sprites/menu/buttons/special_button");










    //slider
    initSprite(&Sprites->mainMenuSlider, 4, "./assets/sprites/menu/buttons/slider_btn/");

    //slider btns
    initSprite(&Sprites->sldPlsBtn, 3, "./assets/sprites/menu/buttons/slider_click_btn/plus/");
    
    initSprite(&Sprites->sldMnsBtn, 3, "./assets/sprites/menu/buttons/slider_click_btn/mins/");

    //check box
    initSprite(&Sprites->check_btn, 2, "./assets/sprites/menu/buttons/check_btn/");

    //close btn
    initSprite(&Sprites->closeBtn, 3, "./assets/sprites/menu/buttons/close btn/");

}

void loadAllSprites(Sprites *Sprites){

    loadMenuSprites(Sprites);

}

void cleanMenuSprites(Sprites *Sprites){
    cleanupSprite(&Sprites->menuMainBg);
    cleanupSprite(&Sprites->mPlay_btn);
    cleanupSprite(&Sprites->mOption_btn);
    cleanupSprite(&Sprites->mQuit_btn);
    cleanupSprite(&Sprites->mainMenuSlider);
}

void CleanAllSprites(Sprites *Sprites) {
    if (Sprites != NULL) {
        cleanMenuSprites(Sprites);
        //free(Sprites);
    }
}



void initButton(Button *btn, char* btn_name, Sprite sprite, int x, int y){
    
    btn->alive = 1;

    btn->x = x;
    btn->y = y;

    btn->spr = sprite;

    btn->w = sprite.w;
    btn->h = sprite.h;

    btn->state = 0;

    btn->btn_name = btn_name;
}

void showButton(Button btn, SDL_Surface* screen){
    if (btn.alive){
        // Set the position of the image
        SDL_Rect destinationRect = {btn.x, btn.y, 0, 0};

        // Blit the current image onto the screen at the specified position
        SDL_BlitSurface(btn.spr.image[btn.state], NULL, screen, &destinationRect);
    }
}

void initSlider(SliderBar *sld_bar, char* slider_name, Sprite sprite, int x, int y, Sprites sprs){
    
    sld_bar->alive = 1;

    sld_bar->x = x;
    sld_bar->y = y;

    sld_bar->spr = sprite;

    sld_bar->w = sprite.w;
    sld_bar->h = sprite.h;

    sld_bar->state = 3;

    sld_bar->slider_name = slider_name;

    int sldbtn_x1, sldbtn_x2, sldbtn_y;
    sldbtn_x1 = sld_bar->x - 80;
    sldbtn_x2 = sld_bar->x + sld_bar->w + 30;
    sldbtn_y = sld_bar->y + 5;

    if (strcmp(slider_name, "music") == 0){
        initButton(&sld_bar->minsBtn, "msc_mns_btn", sprs.sldMnsBtn, sldbtn_x1, sldbtn_y);
        initButton(&sld_bar->plusBtn, "msc_pls_btn", sprs.sldPlsBtn, sldbtn_x2, sldbtn_y);
    }
    else if (strcmp(slider_name, "sfx") == 0){
        initButton(&sld_bar->minsBtn, "sfx_mns_btn", sprs.sldMnsBtn, sldbtn_x1, sldbtn_y);
        initButton(&sld_bar->plusBtn, "sfx_pls_btn", sprs.sldPlsBtn, sldbtn_x2, sldbtn_y);
    }
}

void sliderUpdateVolume(Sounds *sounds, SliderBar *slider) {
    int volume;

    // Determine the volume based on the slider state
    switch (slider->state) {
        case 0: // Mute
            volume = 0;
            break;
        case 1:
            volume = 32; // Adjust as needed
            break;
        case 2:
            volume = 64; // Adjust as needed
            break;
        case 3: // Max volume
            volume = 128;
            break;
        default:
            // Handle invalid state
            volume = 0;
            break;
    }

    // Set the volume for music and sound effects
    if (strcmp(slider->slider_name, "music") == 0)
    {
        setMusicVolume(sounds, volume);
    }
    else if (strcmp(slider->slider_name, "sfx") == 0)
    {
        setSfxVolume(sounds, volume);
    }
}

void sliderUpdateState(SliderBar *sld_bar, int action, Sounds *sounds){
    int new_state = sld_bar->state;
    new_state += action;
    if (new_state > 3){
        new_state = 3;
    }
    if (new_state < 0){
        new_state = 0;
    }

    sld_bar->state = new_state;

    sliderUpdateVolume(sounds, sld_bar);
}

void showSlider(SliderBar sld_bar, SDL_Surface* screen){
    if (sld_bar.alive){
        // Set the position of the image
        SDL_Rect destinationRect = {sld_bar.x, sld_bar.y, 0, 0};

        // Blit the current image onto the screen at the specified position
        SDL_BlitSurface(sld_bar.spr.image[sld_bar.state], NULL, screen, &destinationRect);

        showButton(sld_bar.plusBtn, screen);
        showButton(sld_bar.minsBtn, screen);
    }
}

// Function to check if a point (x, y) is inside a rectangle
int pointInRect(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}

// Function to check if the mouse is inside a button
int isMouseInsideButton(Button* button, int mouseX, int mouseY) {
    SDL_Rect buttonRect = {button->x, button->y, button->w, button->h};
    int point_in_rec = pointInRect(mouseX, mouseY, buttonRect);
    //printf("%d\n", point_in_rec);
    return point_in_rec;
}

// Function to draw text on the screen
void drawText(SDL_Surface* screen, const char* text, int x, int y, TTF_Font* font, SDL_Color textColor) {
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, textColor);
    
    SDL_Rect destinationRect = {x, y, 0, 0};
    SDL_BlitSurface(textSurface, NULL, screen, &destinationRect);
    
    SDL_FreeSurface(textSurface);
}

/*void drawButonText(Button btn, SDL_Surface* screen, const char* text, TTF_Font* font, SDL_Color textColor){
    int btn_x, btn_y;

    btn_x = ((btn.x + btn.w)/2);
    btn_y = (btn.y + 5);

    //printf("%d %d %d\n",btn_y, btn.y, btn.h);

    drawText(screen, text, btn_x, btn_y, font, textColor);
}*/

void initMainMenu(MainMenu *menu, Sprites sprites){
    menu->bg = sprites.menuMainBg;
    initButton(&menu->playBtn, "play", sprites.mPlay_btn, 700, 190);
    initButton(&menu->optionsBtn, "options", sprites.mOption_btn, 700, 370);
    initButton(&menu->exitBtn, "exit", sprites.mQuit_btn, 700, 550);

    // Load a font
    menu->font = TTF_OpenFont("./assets/fonts/menu/RINGM___.TTF", 72);
    if (menu->font == NULL) {
        fprintf(stderr, "Could not load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    SDL_Color textColor =  {255,255, 255}; // White color;
    SDL_Color textColor2 = {200,121, 72}; //{245,188, 135}; // White color;

    menu->textColor = textColor;
    menu->textColor2 = textColor2;

    // init the options menu
    initOptionsMenu(menu, sprites);
    initPLayMenu(menu, sprites);
    initpauseMenu(menu, sprites);
    initskinMenu(menu, sprites);
    initcontrolsMenu(menu, sprites);

}

void controlMainMenu(MainMenu *menu, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen){
    // Handle user input
    
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                *quit = 1;
                
                break;
            case SDL_KEYDOWN:
                switch (event->key.keysym.sym) {
                    case SDLK_p:
                        // Simulate a click on the play button
                        menu->playBtn.state = 2;
                        playSoundEffect(sounds.btnClickSndEffect);
                        SDL_Delay(500);
                        *curren_screen = 3;
                        break;
                    case SDLK_o:
                        // Simulate a click on the options button
                        menu->optionsBtn.state = 2;
                        playSoundEffect(sounds.btnClickSndEffect);
                        SDL_Delay(500);
                        *curren_screen = 2;
                        break;
                    case SDLK_e:
                        // Simulate a click on the exit button
                        menu->exitBtn.state = 2;
                        playSoundEffect(sounds.btnClickSndEffect);
                        SDL_Delay(500);
                        *quit = 1;
                        break;
                    case SDLK_ESCAPE:
                        // Quit the program on Escape key
                        *quit = 1;
                        break;
                }
                break;
        }
    }
   
    

    int mouseX, mouseY;
    int currentMouseButtonState = SDL_GetMouseState(&mouseX, &mouseY);

    ///play
    if (isMouseInsideButton(&menu->playBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->playBtn.state = 2;
            playSoundEffect(sounds.btnClickSndEffect);
            SDL_Delay(500);
            *curren_screen = 3;
        }
        else{
            //hover
            if (menu->playBtn.state != 1){
                menu->playBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->playBtn.state = 0;
    }

    ///options
    if (isMouseInsideButton(&menu->optionsBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->optionsBtn.state = 2;
            playSoundEffect(sounds.btnClickSndEffect);
            SDL_Delay(500);
            *curren_screen = 2;
        }
        else{
            //hover
            if (menu->optionsBtn.state != 1){
                menu->optionsBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->optionsBtn.state = 0;
    }
    

    ///exit
    if (isMouseInsideButton(&menu->exitBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->exitBtn.state = 2;
            playSoundEffect(sounds.btnClickSndEffect);
            SDL_Delay(500);
            *quit = 1;
        }
        else{
            //hover
            if (menu->exitBtn.state != 1){
                menu->exitBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->exitBtn.state = 0;
    }
    
}

void showMainMenu(MainMenu *menu, SDL_Surface* screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen){

    controlMainMenu(menu, event, sounds, quit, curren_screen);

    //bg
    showSprite(&menu->bg, screen, 0, 0);

    //title
    drawText(screen, "REBIRTH", 676, 50, menu->font, menu->textColor);
    drawText(screen, "REBIRTH", 671, 50, menu->font, menu->textColor2);

    //btns
    showButton(menu->playBtn, screen);
    showButton(menu->optionsBtn, screen);
    showButton(menu->exitBtn, screen);

    // Draw text using the font
    /*drawButonText(menu->playBtn, screen, "Play", menu->font, menu->textColor);
    drawButonText(menu->optionsBtn, screen, "Options", menu->font, menu->textColor);
    drawButonText(menu->exitBtn, screen, "Exit", menu->font, menu->textColor);*/

}

void initOptionsMenu(MainMenu *menu, Sprites sprites){
    menu->optionbg = sprites.menuoptionbg;
    initSlider(&menu->options_menu.musicSlider, "music", sprites.mainMenuSlider, 450, 160, sprites);
    initSlider(&menu->options_menu.sfxSlider, "sfx", sprites.mainMenuSlider, 450, 340, sprites);

    initButton(&menu->options_menu.fullScreenCheckBtn, "full screen", sprites.check_btn, 350, 520);

    initButton(&menu->options_menu.closeBtn, "close btn", sprites.closeBtn, 1190, 70);

    // Load a font
    menu->font = TTF_OpenFont("./assets/fonts/menu/RINGM___.TTF", 20);
    if (menu->font == NULL) {
        fprintf(stderr, "Could not load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    SDL_Color textColor =  {255,255, 255}; // White color;
    SDL_Color textColor2 = {200,121, 72}; //{245,188, 135};


}

void controlOptionsMenu(MainMenu *menu, SDL_Event *event, SDL_Surface* screen, Sounds sounds, int *quit, int *curren_screen){
// Handle user input
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                *quit = 1;
            break; 

            case SDL_KEYDOWN:
                if (event->key.keysym.sym == SDLK_f) {
                    playSoundEffect(sounds.btnClickSndEffect);

                    if (menu->options_menu.fullScreenCheckBtn.state == 0){
                        menu->options_menu.fullScreenCheckBtn.state = 1;
                    } else{
                        menu->options_menu.fullScreenCheckBtn.state = 0;
                    }

                    SDL_WM_ToggleFullScreen(screen);
                    SDL_Delay(250);
                }
            break;
                                case SDLK_ESCAPE:
                        // Quit the program on Escape key
                        *quit = 1;
                        break;
        }
    } 

    int mouseX, mouseY;
    int currentMouseButtonState = SDL_GetMouseState(&mouseX, &mouseY);

    ///music pls
    if (isMouseInsideButton(&menu->options_menu.musicSlider.plusBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->options_menu.musicSlider.plusBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            sliderUpdateState(&menu->options_menu.musicSlider, 1, &sounds);
        }
        else{
            //hover
            if (menu->options_menu.musicSlider.plusBtn.state != 1){
                menu->options_menu.musicSlider.plusBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->options_menu.musicSlider.plusBtn.state = 0;
    }

    ///music mns
    if (isMouseInsideButton(&menu->options_menu.musicSlider.minsBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->options_menu.musicSlider.minsBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            sliderUpdateState(&menu->options_menu.musicSlider, -1, &sounds);
        }
        else{
            //hover
            if (menu->options_menu.musicSlider.minsBtn.state != 1){
                menu->options_menu.musicSlider.minsBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->options_menu.musicSlider.minsBtn.state = 0;
    }

    ///sfx pls
    if (isMouseInsideButton(&menu->options_menu.sfxSlider.plusBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->options_menu.sfxSlider.plusBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            sliderUpdateState(&menu->options_menu.sfxSlider, 1, &sounds);
        }
        else{
            //hover
            if (menu->options_menu.sfxSlider.plusBtn.state != 1){
                menu->options_menu.sfxSlider.plusBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->options_menu.sfxSlider.plusBtn.state = 0;
    }

    ///music mns
    if (isMouseInsideButton(&menu->options_menu.sfxSlider.minsBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->options_menu.sfxSlider.minsBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            sliderUpdateState(&menu->options_menu.sfxSlider, -1, &sounds);
        }
        else{
            //hover
            if (menu->options_menu.sfxSlider.minsBtn.state != 1){
                menu->options_menu.sfxSlider.minsBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->options_menu.sfxSlider.minsBtn.state = 0;
    }

    ///full screnn
    if (isMouseInsideButton(&menu->options_menu.fullScreenCheckBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            playSoundEffect(sounds.btnClickSndEffect);

            if (menu->options_menu.fullScreenCheckBtn.state == 0){
                menu->options_menu.fullScreenCheckBtn.state = 1;
            } else{
                menu->options_menu.fullScreenCheckBtn.state = 0;
            }

            SDL_WM_ToggleFullScreen(screen);
            SDL_Delay(250);

        }
        
    }

      ///close
    if (isMouseInsideButton(&menu->options_menu.closeBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->options_menu.closeBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            *curren_screen = 1;
        }
        else{
            //hover
            if (menu->options_menu.closeBtn.state != 1){
                menu->options_menu.closeBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->options_menu.closeBtn.state = 0;
    }

}

void showOptionsMenu(MainMenu *menu, SDL_Surface* screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen){

    controlOptionsMenu(menu, event, screen, sounds, quit, curren_screen);

    //bg
    showSprite(&menu->optionbg, screen, 0, 0);

    //title
    drawText(screen, "Settings", 470, 10, menu->font, menu->textColor);

    //btns
    showSlider(menu->options_menu.musicSlider, screen);
    showSlider(menu->options_menu.sfxSlider, screen);

    showButton(menu->options_menu.fullScreenCheckBtn, screen);
    drawText(screen, "Full screen", menu->options_menu.fullScreenCheckBtn.x + 100, menu->options_menu.fullScreenCheckBtn.y - 10, menu->font, menu->textColor);

    showButton(menu->options_menu.closeBtn, screen);

}
//play menu

void initPLayMenu(MainMenu *menu, Sprites sprites){

    menu->playbg = sprites.menuplaybg;
    
    initButton(&menu->play_menu.newgameBtn, "new game", sprites.newgame_Btn, 20, 175);

    initButton(&menu->play_menu.loadgameBtn, "load game", sprites.loadgame_Btn, 20, 375);

    initButton(&menu->play_menu.closeBtn, "close btn", sprites.pclose_Btn, 1190, 70);

    // Load a font
    menu->font = TTF_OpenFont("./assets/fonts/menu/RINGM___.TTF", 72);
    if (menu->font == NULL) {
        fprintf(stderr, "Could not load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    SDL_Color textColor =  {255,255, 255}; // White color;
    SDL_Color textColor2 = {200,121, 72}; //{245,188, 135};


}

void controlPLayMenu(MainMenu *menu, SDL_Event *event, SDL_Surface* screen, Sounds sounds, int *quit, int *curren_screen){
// Handle user input
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                *quit = 1;
            break; 

        }
    } 

    int mouseX, mouseY;
    int currentMouseButtonState = SDL_GetMouseState(&mouseX, &mouseY);
    

    ///new game
    if (isMouseInsideButton(&menu->play_menu.newgameBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->play_menu.newgameBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            *curren_screen = 7;
        }
        else{
            //hover
            if (menu->play_menu.newgameBtn.state != 1){
                menu->play_menu.newgameBtn.state = 1;
            playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->play_menu.newgameBtn.state = 0;
    }

    ///load game
    if (isMouseInsideButton(&menu->play_menu.loadgameBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->play_menu.loadgameBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            *curren_screen = 8;
            
        }
        else{
            //hover
            if (menu->play_menu.loadgameBtn.state != 1){
                menu->play_menu.loadgameBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->play_menu.loadgameBtn.state = 0;
    }

    ///close
    if (isMouseInsideButton(&menu->play_menu.closeBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->play_menu.closeBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            *curren_screen = 1;
        }
        else{
            //hover
            if (menu->play_menu.closeBtn.state != 1){
                menu->play_menu.closeBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->play_menu.closeBtn.state = 0;
    }

}

void showPlayMenu(MainMenu *menu, SDL_Surface* screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen){

    controlPLayMenu(menu, event, screen, sounds, quit, curren_screen);

    //bg
    showSprite(&menu->playbg, screen, 0, 0);

    //title
    drawText(screen, "Play", 470, 10, menu->font, menu->textColor);


   

    showButton(menu->play_menu.newgameBtn, screen);
    showButton(menu->play_menu.loadgameBtn, screen);
    //drawText(screen, "Full screen", menu->options_menu.fullScreenCheckBtn.x + 100, menu->options_menu.fullScreenCheckBtn.y - 10, menu->font, menu->textColor);

    showButton(menu->play_menu.closeBtn, screen);

}

void initpauseMenu(MainMenu *menu, Sprites sprites){
    
    menu->pausebg = sprites.pausebg;
    

    
    initButton(&menu->pause_menu.resumeBtn, "pause game", sprites.resume_Btn, 20, 175);

    initButton(&menu->pause_menu.controlsBtn, "controls", sprites.controls_Btn, 20, 375);

    initButton(&menu->pause_menu.closeBtn, "close btn", sprites.pclose_Btn, 1190, 70);

    // Load a font
    menu->font = TTF_OpenFont("./assets/fonts/menu/RINGM___.TTF", 72);
    if (menu->font == NULL) {
        fprintf(stderr, "Could not load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    SDL_Color textColor =  {136, 8, 8}; // White color;
    SDL_Color textColor2 = {200,121, 72}; //{245,188, 135};


}
void controlPauseMenu(MainMenu *menu, SDL_Event *event, SDL_Surface* screen, Sounds sounds, int *quit, int *curren_screen){
    // Handle user input
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                *quit = 1;
                break;
        }
    }

    int mouseX, mouseY;
    int currentMouseButtonState = SDL_GetMouseState(&mouseX, &mouseY);
    
    ///new game
    if (isMouseInsideButton(&menu->pause_menu.resumeBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->pause_menu.resumeBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            *curren_screen = 5;
        }
        else{
            //hover
            if (menu->pause_menu.resumeBtn.state != 1){
                menu->pause_menu.resumeBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->pause_menu.resumeBtn.state = 0;
    }

    ///load game
    if (isMouseInsideButton(&menu->pause_menu.controlsBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->pause_menu.controlsBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            
        }
        else{
            //hover
            if (menu->pause_menu.controlsBtn.state != 1){
                menu->pause_menu.controlsBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->pause_menu.controlsBtn.state = 0;
    }

    ///close
    if (isMouseInsideButton(&menu->pause_menu.closeBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->pause_menu.closeBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            *curren_screen = 1;
        }
        else{
            //hover
            if (menu->pause_menu.closeBtn.state != 1){
                menu->pause_menu.closeBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->pause_menu.closeBtn.state = 0;
    }

}

void showPauseMenu(MainMenu *menu, SDL_Surface *screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen){

    controlPauseMenu(menu, event, screen, sounds, quit, curren_screen);

    //bg
    showSprite(&menu->pausebg, screen, 0, 0);

    //title
    drawText(screen, "GAME OVER", 470, 10, menu->font, menu->textColor);


   

    showButton(menu->pause_menu.resumeBtn, screen);
    showButton(menu->pause_menu.controlsBtn, screen);
    //drawText(screen, "Full screen", menu->options_menu.fullScreenCheckBtn.x + 100, menu->options_menu.fullScreenCheckBtn.y - 10, menu->font, menu->textColor);

    showButton(menu->pause_menu.closeBtn, screen);

}
void initskinMenu(MainMenu *menu, Sprites sprites){

    menu->play_menu.playbg = sprites.menuMainBg;
    
    initButton(&menu->skin_menu.skin1Btn, "skin1", sprites.skin1_Btn, 550, 375);

    initButton(&menu->skin_menu.skin2Btn, "skin2", sprites.skin2_Btn, 750, 275);

    initButton(&menu->skin_menu.closeBtn, "close btn", sprites.pclose_Btn, 1190, 70);

    // Load a font
    menu->font = TTF_OpenFont("./assets/fonts/menu/RINGM___.TTF", 72);
    if (menu->font == NULL) {
        fprintf(stderr, "Could not load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    SDL_Color textColor =  {136, 8, 8}; // White color;
    SDL_Color textColor2 = {200,121, 72}; //{245,188, 135};


}

void controlskinMenu(MainMenu *menu, SDL_Event *event, SDL_Surface* screen, Sounds sounds, int *quit, int *curren_screen, int *nb_skin){
    // Handle user input
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                *quit = 1;
                break;
        }
    }

    int mouseX, mouseY;
    int currentMouseButtonState = SDL_GetMouseState(&mouseX, &mouseY);
    
    ///skin1
    if (isMouseInsideButton(&menu->skin_menu.skin1Btn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->skin_menu.skin1Btn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            *nb_skin = 1;
            *curren_screen = 5;
            
        }
        else{
            //hover
            if (menu->skin_menu.skin1Btn.state != 1){
                menu->skin_menu.skin1Btn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->skin_menu.skin1Btn.state = 0;
    }

    ///skin2
    if (isMouseInsideButton(&menu->skin_menu.skin2Btn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->skin_menu.skin2Btn.state = 2;
            *nb_skin = 2;
            *curren_screen = 5;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            
        }
        else{
            //hover
            if (menu->skin_menu.skin2Btn.state != 1){
                menu->skin_menu.skin2Btn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->skin_menu.skin2Btn.state = 0;
    }

    ///close
    if (isMouseInsideButton(&menu->skin_menu.closeBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->skin_menu.closeBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            *curren_screen = 1;
            
        }
        else{
            //hover
            if (menu->skin_menu.closeBtn.state != 1){
                menu->skin_menu.closeBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->skin_menu.closeBtn.state = 0;
    }

}

void showSkinMenu(MainMenu *menu, SDL_Surface *screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen, int *nb_skin) {
    controlskinMenu(menu, event, screen, sounds, quit, curren_screen, nb_skin);

    // bg
    showSprite(&menu->bg, screen, 0, 0);  
        //title
    drawText(screen, "choose your drip", 470, 10, menu->font, menu->textColor);


   

    showButton(menu->skin_menu.skin1Btn, screen);
    showButton(menu->skin_menu.skin2Btn, screen);

    //drawText(screen, "Full screen", menu->options_menu.fullScreenCheckBtn.x + 100, menu->options_menu.fullScreenCheckBtn.y - 10, menu->font, menu->textColor);

    showButton(menu->skin_menu.closeBtn, screen);

}

void initcontrolsMenu(MainMenu *menu, Sprites sprites){

    menu->controls_menu.bg = sprites.menuMainBg;
    
    initButton(&menu->controls_menu.attackBtn, "attack", sprites.attack_Btn, 20, 375);

    initButton(&menu->controls_menu.specialBtn, "special", sprites.special_Btn, 20, 675);

    //initButton(&menu->controls_menu.jumpBtn, "jump", sprites.jump_Btn, 750, 275);

    //initButton(&menu->controls_menu.leftBtn, "left", sprites.left_Btn, 750, 275);

    //initButton(&menu->controls_menu.rightBtn, "right", sprites.right_Btn, 750, 275);

    initButton(&menu->controls_menu.closeBtn, "close btn", sprites.pclose_Btn, 1190, 70);

    // Load a font
    menu->font = TTF_OpenFont("./assets/fonts/menu/RINGM___.TTF", 72);
    if (menu->font == NULL) {
        fprintf(stderr, "Could not load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    SDL_Color textColor =  {136, 8, 8}; // White color;
    SDL_Color textColor2 = {200,121, 72}; //{245,188, 135};


}

void controlsControlsMenu(MainMenu *menu, SDL_Event *event, SDL_Surface* screen, Sounds sounds, int *quit, int *curren_screen, KeyConfig *keys){
    // Handle user input
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                *quit = 1;
                break;
                case SDL_KEYDOWN:
                // Check if the user selects an action to modify
                if (menu->getting_key_on) {
                    if (event->key.keysym.sym != SDLK_ESCAPE) {
                        // Update the keybinding for the selected action
                        if (menu->pressed_key == 1) {
                            keys->attack = event->key.keysym.sym;
                            printf("New attack key: %s\n", SDL_GetKeyName(keys->attack));
                        } else if (menu->pressed_key == 2) {
                            keys->special = event->key.keysym.sym;
                            printf("New special key: %s\n", SDL_GetKeyName(keys->special));
                        }
                    }
                    menu->getting_key_on = 0; // Done modifying
                }
                break;
        }
    }
        


    int mouseX, mouseY;
    int currentMouseButtonState = SDL_GetMouseState(&mouseX, &mouseY);
    
    ///attck
    if (isMouseInsideButton(&menu->controls_menu.attackBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->controls_menu.attackBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            menu->getting_key_on = 1; // Start modifying keybinding
            menu->pressed_key = 1; // Attack key
            //printf("New attack key: %s\n", SDL_GetKeyName(keys->attack));
            
            
            
        }
        else{
            //hover
            if (menu->controls_menu.attackBtn.state != 1){
                menu->controls_menu.attackBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->controls_menu.attackBtn.state = 0;
    }

    ///special attack
    if (isMouseInsideButton(&menu->controls_menu.specialBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->controls_menu.specialBtn.state = 2;
                
            menu->getting_key_on = 1; // Start modifying keybinding
            menu->pressed_key = 2; // spcialattck key
                 //printf("New special attack key: %s\n", SDL_GetKeyName(keys->special));
             
            
            
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            
        }
        else{
            //hover
            if (menu->controls_menu.specialBtn.state != 1){
                menu->controls_menu.specialBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->controls_menu.specialBtn.state = 0;
    }

    ///close
    if (isMouseInsideButton(&menu->controls_menu.closeBtn, mouseX, mouseY)){
        if (currentMouseButtonState){
            //click
            menu->controls_menu.closeBtn.state = 2;
            SDL_Delay(250);
            playSoundEffect(sounds.btnClickSndEffect);
            *curren_screen = 3;
            
        }
        else{
            //hover
            if (menu->controls_menu.closeBtn.state != 1){
                menu->controls_menu.closeBtn.state = 1;
                playSoundEffect(sounds.btnHoverSndEffect);
            }
        }
    }else{
        menu->controls_menu.closeBtn.state = 0;
    }

}

void showControlsMenu(MainMenu *menu, SDL_Surface *screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen, KeyConfig *keys) {
    controlsControlsMenu(menu, event, screen, sounds, quit, curren_screen, keys);

    // bg
    showSprite(&menu->bg, screen, 0, 0);  
        //title
    drawText(screen, "change your controls", 470, 10, menu->font, menu->textColor);


   

    showButton(menu->controls_menu.attackBtn, screen);
    showButton(menu->controls_menu.specialBtn, screen);

    //drawText(screen, "Full screen", menu->options_menu.fullScreenCheckBtn.x + 100, menu->options_menu.fullScreenCheckBtn.y - 10, menu->font, menu->textColor);

    showButton(menu->controls_menu.closeBtn, screen);

}








    
    
    

void initMenu(MainMenu *main_menu, Sprites sprites){
    initMainMenu(main_menu, sprites);
}

void showMenu(MainMenu *main_menu, SDL_Surface* screen, SDL_Event *event, Sounds sounds, int *quit, int *curren_screen,int *nb_skin, KeyConfig *keys) {
    if (*curren_screen == 1){
        showMainMenu(main_menu, screen, event, sounds, quit, curren_screen);
    }

    else if (*curren_screen == 2){
        showOptionsMenu(main_menu, screen, event, sounds, quit, curren_screen);
    }
//new menu here

    else if (*curren_screen == 3){
        showPlayMenu(main_menu, screen, event, sounds, quit, curren_screen);
    }

    else if (*curren_screen == 4){
        playSoundEffect(sounds.pausesndeffect);
        showPauseMenu(main_menu, screen, event, sounds, quit, curren_screen);
    }

    else if (*curren_screen == 7) {
        showSkinMenu(main_menu, screen, event, sounds, quit, curren_screen, nb_skin);
    }
    else if (*curren_screen == 8) {
        showControlsMenu(main_menu, screen, event, sounds, quit, curren_screen, keys);
    }


}

int printPressedKeys(const Uint8 *keystate) {
    int pressedKeyCode = SDLK_UNKNOWN;

    for (int key = 0; key < SDLK_LAST; key++) {
        if (keystate[key] && keystate[SDLK_LAST] != keystate[key]) {
            pressedKeyCode = key;
            //const char* keyName = SDL_GetKeyName((SDLKey)key);
            //printf("Pressed key: %s\n", keyName);
            break;
        }
    }

    if (pressedKeyCode != 300 && pressedKeyCode != 301){
        return pressedKeyCode;
    }
    else{
        return 0;
    }
}

void ChangeControls(MainMenu *menu){

    if (menu->getting_key_on){
        //printf("%d\n",printPressedKeys(menu->keystate));
        menu->pressed_key = printPressedKeys(menu->keystate);

        if (menu->pressed_key != 0){

            menu->getting_key_on = 0;

            


            



        }
    }
}

