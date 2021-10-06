#ifndef LIB_PLAYER_H_INCLUDED
#define LIB_PLAYER_H_INCLUDED
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"

//struct containing all values for a player
typedef struct Players{
    int playerLife;
    float money;
    int enemiesInWave;
    SDL_Rect rect;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect2;
    SDL_Surface* surface2;
    SDL_Texture* texture2;
} Player;

//Rectangle of players life images
SDL_Rect lSpriteClips[3];
//Load all images to players life
void loadMediaPlayerLife(SDL_Renderer* render);
//Create a player struct
Player* CreatePlayer(SDL_Renderer* render);

#endif

