//#define SCREEN_W 800 //ordh l ecran
//#define SCREEN_H 480 //toul l ecran


typedef struct 
{
	SDL_Surface* image[30]; 
	SDL_Surface *background_GameOver, *background_Victory; 
	SDL_Rect PositionBackground; 
        int current_frame, previous_frame; 
	SDL_Surface *ImageOriginale, *ImageModifiee; 
	SDL_Rect PositionImageOriginale, PositionImageModifiee; 
	int ReponseCorrecte; 
	Mix_Music *musique_enigme, *musique_victoire, *musique_defaite; 
}enigme;

void initialiserEnigme(enigme* e); 
void afficherEnigme(enigme e, SDL_Surface* screen); 
void animerEnigme(enigme* e); 
void genererEnigme(enigme *e); 
void freeEnigme(enigme e); 
void interface_win(SDL_Surface* screen, int* boucle, enigme e); 
void interface_lose(SDL_Surface* screen, int* boucle, enigme e); 
int generateRandomNumber(int min, int max); 









