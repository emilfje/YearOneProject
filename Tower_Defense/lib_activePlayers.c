#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "lib_activePlayers.h"
#include "SDL.h"
#include "SDL_image.h"
#include "lib_menu.h"

Player* CreatePlayer(SDL_Renderer* render)
{
    Player *NewPlayer = malloc(sizeof(Player));

    NewPlayer->surface = IMG_Load("resources/playerLifeSprite.png");
    NewPlayer->texture = SDL_CreateTextureFromSurface(render, NewPlayer->surface);
    SDL_QueryTexture(NewPlayer->texture, NULL, NULL, &NewPlayer->rect.w, &NewPlayer->rect.h);

    NewPlayer->surface2 = IMG_Load("resources/coin.png");
    NewPlayer->texture2 = SDL_CreateTextureFromSurface(render, NewPlayer->surface2);

    NewPlayer->enemiesInWave = 0;
    NewPlayer->playerLife = 3;
    NewPlayer->money = 100;
    NewPlayer->rect.x = WINDOW_WIDTH - 460;
    NewPlayer->rect.y = WINDOW_HEIGHT/2-85;
    NewPlayer->rect.h = 70;
    NewPlayer->rect.w = 200;
    NewPlayer->rect2.w = 70;
    NewPlayer->rect2.h = 70;
    NewPlayer->rect2.x = NewPlayer->rect.x + NewPlayer->rect.w + 20;
    NewPlayer->rect2.y = NewPlayer->rect.y;
    return NewPlayer;
}

void loadMediaPlayerLife(SDL_Renderer* render)
{

    lSpriteClips[ 0 ].x =   0;
    lSpriteClips[ 0 ].y =   0;
    lSpriteClips[ 0 ].w =  200;
    lSpriteClips[ 0 ].h = 70;

    lSpriteClips[ 1 ].x =  200;
    lSpriteClips[ 1 ].y =   0;
    lSpriteClips[ 1 ].w =  200;
    lSpriteClips[ 1 ].h = 70;

    lSpriteClips[ 2 ].x = 400;
    lSpriteClips[ 2 ].y =   0;
    lSpriteClips[ 2 ].w =  200;
    lSpriteClips[ 2 ].h = 70;

}
