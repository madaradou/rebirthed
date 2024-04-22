#include "image.h"


#include <limits.h> // Include for INT_MIN and INT_MAX
#include <stdlib.h> // Include for rand() and srand()
#include <time.h>   // Include for seeding srand()
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_image.h>


void initBackground(Image* Backg) {
    Backg->img = IMG_Load("assets/tic/backgrounds/animation/yassine.jpg");
    if (Backg->img == NULL) {
        printf("Unable to load background image: %s\n", IMG_GetError());
        return;
    }
    Backg->pos1.x = 0;
    Backg->pos1.y = 0;
    Backg->pos1.w = SCREEN1_W;
    Backg->pos1.h = SCREEN1_H;
    Backg->pos2 = Backg->pos1;
}

void liberer(Image* A) {
    SDL_FreeSurface(A->img);
}

void afficher(Image p, SDL_Surface* screen) {
    SDL_BlitSurface(p.img, &p.pos2, screen, &p.pos1);
}

void afficherTic(tic t, SDL_Surface* ecran) {
    SDL_Surface *x_img = IMG_Load("assets/tic/x&o/x.png");
    SDL_Surface *o_img = IMG_Load("assets/tic/x&o/o.png");

    if (x_img == NULL || o_img == NULL) {
        printf("Unable to load X or O image: %s\n", IMG_GetError());
        return;
    }

    int square_width = SCREEN1_W / 3;
    int square_height = SCREEN1_H / 3;

    for (int i = 0; i < NUM_SQUARES; i++) {
        int row = i / 3;
        int col = i % 3;
        SDL_Rect square_pos;
        square_pos.x = col * square_width;
        square_pos.y = row * square_height;
        square_pos.w = square_width;
        square_pos.h = square_height;

        if (t.tabsuivi[i] == 1) {
            SDL_BlitSurface(o_img, NULL, ecran, &square_pos);
        } else if (t.tabsuivi[i] == -1) {
            SDL_BlitSurface(x_img, NULL, ecran, &square_pos);
        }
    }

    SDL_FreeSurface(x_img);
    SDL_FreeSurface(o_img);
}

int atilganer(int tabsuivi[]) {
    // Winning lines
    int winning_lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6}             // diagonals
    };

    for (int i = 0; i < 8; i++) {
        if (tabsuivi[winning_lines[i][0]] != 0 && 
            tabsuivi[winning_lines[i][0]] == tabsuivi[winning_lines[i][1]] && 
            tabsuivi[winning_lines[i][0]] == tabsuivi[winning_lines[i][2]]) {
            return tabsuivi[winning_lines[i][0]];
        }
    }
    return 0;
}

void Resultat(int tabsuivi[], SDL_Surface* ecran) {
    int winner = atilganer(tabsuivi);
    char result_text[50];

    if (winner == 1) {
        strcpy(result_text, "The computer wins!");
    } else if (winner == -1) {
        strcpy(result_text, "You win!");
    } else {
        strcpy(result_text, "Draw!");
    }
    // Display result text on the screen
}

void libererMemoire(tic t) {
    SDL_FreeSurface(t.x_img);
    SDL_FreeSurface(t.o_img);
    TTF_CloseFont(t.font);
    t.font = NULL;
    TTF_Quit();
}

int minimax(int tabsuivi[9], int joueur) {
    int winner = atilganer(tabsuivi);

    if (winner != 0) {
        if ((joueur == 1) && (winner == 1)) {
            return 1;
        } else if ((joueur == -1) && (winner == -1)) {
            return -1;
        } else {
            return 0;
        }
    }

    int best_value;
    if (joueur == 1) {
        best_value = INT_MIN;
    } else {
        best_value = INT_MAX;
    }

    for (int i = 0; i < NUM_SQUARES; i++) {
        if (tabsuivi[i] == 0) {
            tabsuivi[i] = joueur;
            int move_value = minimax(tabsuivi, -joueur);
            tabsuivi[i] = 0;
            if (joueur == 1) {
                best_value = (best_value > move_value) ? best_value : move_value;
            } else {
                best_value = (best_value < move_value) ? best_value : move_value;
            }
        }
    }

    return best_value;
}

void calcul_coup(int tabsuivi[9]) {
    int best_value = INT_MIN;
    int best_move = -1;

    for (int i = 0; i < NUM_SQUARES; i++) {
        if (tabsuivi[i] == 0) {
            tabsuivi[i] = 1; // Simulate move for the computer player
            int move_value = minimax(tabsuivi, -1); // Calculate value using minimax
            tabsuivi[i] = 0; // Undo the move

            if (move_value > best_value) {
                best_value = move_value;
                best_move = i;
            }
        }
    }

    if (best_move != -1) {
        printf("The next move is at square %d\n", best_move);
        tabsuivi[best_move] = 1; // Update the game board with the best move
    } else {
        printf("No valid move found.\n");
    }
}

void makeComputerMove(tic *t) {
    int availableMoves[NUM_SQUARES];
    int numAvailableMoves = 0;

    // Determine available moves
    for (int i = 0; i < NUM_SQUARES; i++) {
        if (t->tabsuivi[i] == 0) {
            availableMoves[numAvailableMoves] = i;
            numAvailableMoves++;
        }
    }

    // Choose a random available move
    if (numAvailableMoves > 0) {
        srand(time(NULL)); // Seed the random number generator
        int randomIndex = rand() % numAvailableMoves;
        int chosenMove = availableMoves[randomIndex];
        t->tabsuivi[chosenMove] = 1; // Computer's move
    }
}

// Animation functions

void initAnimation(Animation *anim, const char* framePaths[]) {
    for (int i = 0; i < 6; i++) {
        anim->frames[i] = IMG_Load(framePaths[i]);
        if (!anim->frames[i]) {
            printf("Unable to load animation frame %d: %s\n", i, IMG_GetError());
            // Handle error
        }
    }
    anim->currentFrame = 0;
    anim->pos.x = 0;
    anim->pos.y = 0;
}

void updateAnimation(Animation *anim) {
    anim->currentFrame = (anim->currentFrame + 1) % 6; // Cycle through frames
}

void drawAnimation(Animation anim, SDL_Surface *screen) {
    SDL_BlitSurface(anim.frames[anim.currentFrame], NULL, screen, &anim.pos);
}

void freeAnimation(Animation *anim) {
    for (int i = 0; i < 6; i++) {
        SDL_FreeSurface(anim->frames[i]);
    }
}


void initBackgroundLoser(Loser* Backg) {

    Backg->img = IMG_Load("assets/tic/backgrounds/background/backgroundloser/loser_background.jpg");

    if (Backg->img == NULL) {

        printf("Unable to load background image: %s\n", IMG_GetError());

        return;

    }

    Backg->pos1.x = 0;

    Backg->pos1.y = 0;

    Backg->pos1.w = LOSER_SCREEN_W;

    Backg->pos1.h = LOSER_SCREEN_H;

}



void libererLoser(Loser* A) {

    SDL_FreeSurface(A->img);

}

void eraseSurface(SDL_Surface* screen, SDL_Rect rect) {
    SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0));
}



void afficherLoser(Loser p, SDL_Surface* screen) {

    SDL_BlitSurface(p.img, NULL, screen, &p.pos1);

}


void zoomText(SDL_Surface* screen, TTF_Font* font, SDL_Color color) {

    int fontSize = 30; // Initial font size

    SDL_Surface* textSurface = NULL;

    SDL_Rect textPos;



    int done = 0;

    while (!done) {

        // Increase font size gradually

        if (fontSize < TEXT_MAX_SIZE) {

            TTF_CloseFont(font);

            font = TTF_OpenFont("assets/tic/fonts/modartial.ttf", fontSize++);

            textSurface = TTF_RenderText_Solid(font, "HARD LUCK", color);

        }



        // Center the text on the screen

        textPos.x = LOSER_SCREEN_W / 2 - textSurface->w / 2;

        textPos.y = LOSER_SCREEN_H / 2 - textSurface->h / 2;

        

        SDL_BlitSurface(textSurface, NULL, screen, &textPos);

        SDL_Flip(screen);



        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {

                done = 1;

            }

        }

        SDL_Delay(50); // Control the speed of zooming

    }



    SDL_FreeSurface(textSurface);

}

void afficherBackgroundLoser(Loser BackgLoser, SDL_Surface* screen) {
    SDL_BlitSurface(BackgLoser.img, NULL, screen, &BackgLoser.pos1);
}

void initBackgroundwinner(Winner* Backg) {
    Backg->img = IMG_Load("assets/tic/backgrounds/background/backgroundwinner/winner backgound.jpg");
    if (Backg->img == NULL) {
        printf("Unable to load background image: %s\n", IMG_GetError());
        return;
    }

    Backg->pos1.x = 0;
    Backg->pos1.y = 0;
    Backg->pos1.w = SCREEN1_W;
    Backg->pos1.h = SCREEN1_H;
}

void libererwinner(Winner* A) {
    SDL_FreeSurface(A->img);
}

void afficherwinner(Winner p, SDL_Surface* screen) {
    SDL_BlitSurface(p.img, NULL, screen, &p.pos1);
}

void rotationtext(SDL_Surface* textSurface, SDL_Surface* screen, int* done) {
    static double angle = 0.0;
    angle += 360.0 * 20 *  (1.0 / SDL_GetTicks());

    SDL_Surface* rotatedTextSurface = rotozoomSurface(textSurface, angle, 1.0, 1);
    SDL_Rect textPos = {SCREEN1_W / 2 - rotatedTextSurface->w / 2, SCREEN1_H / 2 - rotatedTextSurface->h / 2, 0, 0};
    SDL_BlitSurface(rotatedTextSurface, NULL, screen, &textPos);

    SDL_Flip(screen);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *done = 1;
        }
    }

    SDL_FreeSurface(rotatedTextSurface);
}


