#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "pandaAnimation.h"
#include "SDL.h"
#include "SDL_image.h"
#include "math.h"


void loadMediaPanda(SDL_Renderer* rend)
{
    pSpriteClips[ 0 ].x =   0;
    pSpriteClips[ 0 ].y =   0;
    pSpriteClips[ 0 ].w =  48;
    pSpriteClips[ 0 ].h = 48;

    pSpriteClips[ 1 ].x =  48;
    pSpriteClips[ 1 ].y =   0;
    pSpriteClips[ 1 ].w =  48;
    pSpriteClips[ 1 ].h = 48;

    pSpriteClips[ 2 ].x =   96;
    pSpriteClips[ 2 ].y =   0;
    pSpriteClips[ 2 ].w =  48;
    pSpriteClips[ 2 ].h = 48;

    pSpriteClips[ 3 ].x =  144;
    pSpriteClips[ 3 ].y =   0;
    pSpriteClips[ 3 ].w =  48;
    pSpriteClips[ 3 ].h = 48;

    pSpriteClips[ 4 ].x =  192;
    pSpriteClips[ 4 ].y =   0;
    pSpriteClips[ 4 ].w =  48;
    pSpriteClips[ 4 ].h = 48;

    pSpriteClips[ 5 ].x =  240;
    pSpriteClips[ 5 ].y =   0;
    pSpriteClips[ 5 ].w =  48;
    pSpriteClips[ 5 ].h = 48;
}

void calculateAngle(Tower* tower, Enemy* enemy)
{
    double opposite;
    double adjacent;
    double angle;
    double angleDegree;
    //pig is to the left of tower and above center
    if(tower->range.x + tower->range.w/2 > enemy->rect.x + enemy->rect.w/2 && tower->range.y + tower->range.h/2 > enemy->rect.y + enemy->rect.h/2)
    {
        opposite = (tower->range.y + tower->range.h/2) - (enemy->rect.y + enemy->rect.h/2);
        adjacent = (tower->range.x + tower->range.w/2) - (enemy->rect.x + enemy->rect.w/2);
        angle = (opposite/adjacent);
        angleDegree = atan(angle) * (180/M_PI);
        tower->frame = 1;
        tower->angle = angleDegree;
        tower->flip = SDL_FLIP_HORIZONTAL;
        if(angleDegree >=45)
        {
            tower->angle = 0;
            tower->flip = SDL_FLIP_NONE;
            tower->frame = 5;
        }
    }
     //pig is to the left of tower and below center
    else if(tower->range.x + tower->range.w/2 > enemy->rect.x + enemy->rect.w/2 && tower->range.y + tower->range.h/2 < enemy->rect.y + enemy->rect.h/2)
    {
        opposite = (tower->range.y + tower->range.h/2) - (enemy->rect.y + enemy->rect.h/2);
        adjacent = (tower->range.x + tower->range.w/2) - (enemy->rect.x + enemy->rect.w/2);
        angle = (opposite/adjacent);
        angleDegree = atan(angle) * (180/M_PI);
        tower->frame = 1;
        tower->angle = angleDegree;
        tower->flip = SDL_FLIP_HORIZONTAL;
        if(angleDegree <=-45)
        {
            tower->angle = 0;
            tower->flip = SDL_FLIP_NONE;
            tower->frame = 3;
        }
    }
    //pig is to the right of tower and above center
    else if(tower->range.x + tower->range.w/2 < enemy->rect.x + enemy->rect.w/2 && tower->range.y + tower->range.h/2 > enemy->rect.y + enemy->rect.h/2)
    {
        opposite = (tower->range.y + tower->range.h/2) - (enemy->rect.y + enemy->rect.h/2);
        adjacent = (enemy->rect.x + enemy->rect.w/2) - (tower->range.x + tower->range.w/2);
        angle = (opposite/adjacent);
        angleDegree = atan(angle) * (180/M_PI) *-1;
        tower->frame = 1;
        tower->angle = angleDegree;
        tower->flip = SDL_FLIP_NONE;
        if(angleDegree <=-45)
        {
            tower->angle = 0;
            tower->frame = 5;
        }
    }
    //pig is to the right of tower and below center
    else if(tower->range.x + tower->range.w/2 < enemy->rect.x + enemy->rect.w/2 && tower->range.y + tower->range.h/2 < enemy->rect.y + enemy->rect.h/2)
    {
        opposite = (enemy->rect.y + enemy->rect.h/2) - (tower->range.y + tower->range.h/2);
        adjacent = (enemy->rect.x + enemy->rect.w/2) - (tower->range.x + tower->range.w/2);
        angle = (opposite/adjacent);
        angleDegree = atan(angle) * (180/M_PI);
        tower->frame = 1;
        tower->angle = angleDegree;
        tower->flip = SDL_FLIP_NONE;
        if(angleDegree >=45)
        {
            tower->angle = 0;
            tower->flip = SDL_FLIP_NONE;
            tower->frame = 3;
        }
    }
}
