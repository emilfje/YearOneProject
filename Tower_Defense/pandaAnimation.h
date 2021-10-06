#ifndef LIB_PANDATANIMATION_H_INCLUDED
#define LIB_PANDATANIMATION_H_INCLUDED
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include "lib_tower.h"
//Cuts the panda sprites into the different frames
SDL_Rect pSpriteClips[6];
//SDL_Rect rSpriteClips[2];

//Loads all the sprite images to the basic tower
void loadMediaPanda(SDL_Renderer* rend);

//Loads all the sprite images to the damage upgrade tower
void loadMediaExplosivePanda(SDL_Renderer* rend);

//Calculates the angle between the center of the tower and an enemy
void calculateAngle(Tower* tower, Enemy* enemy);


#endif
