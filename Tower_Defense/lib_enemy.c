#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "lib_enemy.h"
#include "SDL.h"
#include "SDL_image.h"

Enemy CreateEnemy(SDL_Renderer* render)
{
    Enemy NewEnemy;
    NewEnemy.surface = IMG_Load("resources/GrisSprite.PNG");
    NewEnemy.texture = SDL_CreateTextureFromSurface(render, NewEnemy.surface);
    NewEnemy.life = 10;
    NewEnemy.isHit = 0;
    NewEnemy.rect.x = 1920*0.75;
    NewEnemy.rect.y = 61;
    NewEnemy.rect.h = 100;
    NewEnemy.rect.w = 100;
    NewEnemy.surface2 = IMG_Load("resources/hp2.PNG");
    NewEnemy.texture2 = SDL_CreateTextureFromSurface(render, NewEnemy.surface2);
    NewEnemy.hpBar.x = NewEnemy.rect.x;
    NewEnemy.hpBar.y = NewEnemy.rect.y - 10;
    NewEnemy.hpBar.h = 10;
    NewEnemy.hpBar.w = NewEnemy.rect.w;
    NewEnemy.directions = 2;
    NewEnemy.frame = 5;
    NewEnemy.flip = SDL_FLIP_NONE;
    NewEnemy.frameTime = 0;
    NewEnemy.value = 10;    //Reward when killed
    NewEnemy.numberOfTurns = 0;
    return NewEnemy;
}

void updateHpBar(Enemy* enemy, int enemiesLeftInWave, int enemyMaxLife[])
{
    float enemyCurrentLife[enemiesLeftInWave];
    int fullHpWidth = 100;

    for(int i=0;i<enemiesLeftInWave;i++)
    {
        enemyCurrentLife[i] = enemy[i].life;
        enemy[i].hpBar.w = (enemyCurrentLife[i]/enemyMaxLife[i]) * fullHpWidth;
    }
}

void loadMediaHpBar(SDL_Renderer* rend)
{
    hSpriteClips[ 0 ].x =   0;
    hSpriteClips[ 0 ].y =   0;
    hSpriteClips[ 0 ].w =  35;
    hSpriteClips[ 0 ].h = 19;

    hSpriteClips[ 1 ].x =  35;
    hSpriteClips[ 1 ].y =   0;
    hSpriteClips[ 1 ].w =  35;
    hSpriteClips[ 1 ].h = 19;

    hSpriteClips[ 2 ].x = 70;
    hSpriteClips[ 2 ].y =   0;
    hSpriteClips[ 2 ].w =  35;
    hSpriteClips[ 2 ].h = 19;
}
