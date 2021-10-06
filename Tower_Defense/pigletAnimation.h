#ifndef LIB_PIGLETANIMATION_H_INCLUDED
#define LIB_PIGLETANIMATION_H_INCLUDED
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include "lib_enemy.h"

SDL_Rect gSpriteClips[8];

//Animerar piglet
void animateStruct(Enemy* piglet);

//laddar in spritesheet och delar upp den
void loadMedia(SDL_Renderer* rend);


#endif // LIB_PIGLETANIMATION_H_INCLUDED
