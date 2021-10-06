#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "pigletAnimation.h"
#include "SDL.h"
#include "SDL_image.h"
#include "lib_path.h"
#define RUNSPEED (5)

void animateStruct(Enemy* piglet){
    if(piglet->directions == 0)              // UPPÅT
    {
        piglet->rect.y -= RUNSPEED;
        piglet->hpBar.y -= RUNSPEED;
        piglet->flip = SDL_FLIP_NONE;
        if(piglet->frameTime <= 6)
        {
            piglet->frame = 2;
            piglet->frameTime++;
        }
        else
        {
            piglet->frame = 3;
            piglet->frameTime++;
            if(piglet->frameTime >= 12)
            {
                piglet->frameTime = 0;
            }
        }
    }
    if(piglet->directions == 1)              //NEDÅT
    {
        piglet->rect.y += RUNSPEED;
        piglet->hpBar.y += RUNSPEED;
        piglet->flip = SDL_FLIP_NONE;
        if(piglet->frameTime <= 6)
        {
            piglet->frame = 0;
            piglet->frameTime++;
        }
        else
        {
            piglet->frame = 1;
            piglet->frameTime++;
            if(piglet->frameTime >= 12)
            {
                piglet->frameTime = 0;
            }
        }
    }
    if(piglet->directions == 2)              //VÄNSTER
    {
        piglet->flip = SDL_FLIP_NONE;
        piglet->rect.x -= RUNSPEED;
        piglet->hpBar.x -= RUNSPEED;
        if(piglet->frameTime <= 6)
        {
            piglet->frame = 5;
            piglet->frameTime++;
        }
        else
        {
            piglet->frame = 6;
            piglet->frameTime++;
            if(piglet->frameTime >= 12)
            {
                piglet->frameTime = 0;
            }
        }
    }
    if (piglet->directions == 3)             //HÖGER
    {
        piglet->rect.x += RUNSPEED;
        piglet->hpBar.x += RUNSPEED;
        piglet->flip = SDL_FLIP_HORIZONTAL;
        if(piglet->frameTime <= 6)
        {
            piglet->frame = 5;
            piglet->frameTime++;
        }
        else
        {
            piglet->frame = 6;
            piglet->frameTime++;
            if(piglet->frameTime >= 12)
            {
                piglet->frameTime = 0;
            }
        }
    }
}

void loadMedia(SDL_Renderer* rend){

    gSpriteClips[ 0 ].x =   0;
    gSpriteClips[ 0 ].y =   0;
    gSpriteClips[ 0 ].w =  32;
    gSpriteClips[ 0 ].h = 32;

    gSpriteClips[ 1 ].x =  32;
    gSpriteClips[ 1 ].y =   0;
    gSpriteClips[ 1 ].w =  32;
    gSpriteClips[ 1 ].h = 32;

    gSpriteClips[ 2 ].x = 64;
    gSpriteClips[ 2 ].y =   0;
    gSpriteClips[ 2 ].w =  32;
    gSpriteClips[ 2 ].h = 32;

    gSpriteClips[ 3 ].x = 96;
    gSpriteClips[ 3 ].y =   0;
    gSpriteClips[ 3 ].w =  32;
    gSpriteClips[ 3 ].h = 32;

    gSpriteClips[ 4 ].x = 128;
    gSpriteClips[ 4 ].y =   0;
    gSpriteClips[ 4 ].w =  32;
    gSpriteClips[ 4 ].h = 32;

    gSpriteClips[ 5 ].x = 160;
    gSpriteClips[ 5 ].y =   0;
    gSpriteClips[ 5 ].w =  32;
    gSpriteClips[ 5 ].h = 32;

    gSpriteClips[ 6 ].x = 192;
    gSpriteClips[ 6 ].y =   0;
    gSpriteClips[ 6 ].w =  32;
    gSpriteClips[ 6 ].h = 32;

    gSpriteClips[ 7 ].x = 224;
    gSpriteClips[ 7 ].y =   0;
    gSpriteClips[ 7 ].w =  32;
    gSpriteClips[ 7 ].h = 32;
}


