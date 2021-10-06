#ifndef LIB_PATH_H_INCLUDED
#define LIB_PATH_H_INCLUDED
#include "SDL.h"
#include "SDL_image.h"
#include "lib_enemy.h"

//Changes direction of an enemy when it reaches a certain x/y coordinate
void pathFinding(Enemy* piglet);

#endif // LIB_PATH_H_INCLUDED
