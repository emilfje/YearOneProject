#ifndef LIB_ENEMY_H_INCLUDED
#define LIB_ENEMY_H_INCLUDED
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"

//struct containing all values for the enemies (pigs)
typedef struct Enemies
{
    int life;
    int frame;
    int frameTime;
    int directions;
    int isHit;
    int value;
    int numberOfTurns;
    SDL_RendererFlip flip;
    SDL_Rect rect;
    SDL_Surface* surface;
    SDL_Surface* surface2;
    SDL_Texture* texture;
    SDL_Texture* texture2;
    SDL_Rect hpBar;
} Enemy;

SDL_Rect hSpriteClips[3];

//Function for creating an enemy
Enemy CreateEnemy(SDL_Renderer* render);

//update hpbar when an enemy is hit
void updateHpBar(Enemy* enemy, int enemiesLeftInWave, int enemyMaxLife[]);
//load hp bar
void loadMediaHpBar(SDL_Renderer* rend);
#endif
