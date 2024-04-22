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

void ChangeControls(Menu *menu){

    if (menu->getting_key_on){
        //printf("%d\n",printPressedKeys(menu->keystate));
        menu->pressed_key = printPressedKeys(menu->keystate);

        if (menu->pressed_key != 0){

            menu->getting_key_on = 0;

            


            



        }
    }
}
