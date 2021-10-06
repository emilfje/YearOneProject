#ifndef LIB_WAVE_H_INCLUDED
#define LIB_WAVE_H_INCLUDED
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"

//Array of struct containing the enemies
Enemy pigletArmy[100];

//Creates a wave of enemies with call to createEnemy from lib_enenmy
void createMonsterWave(int* nrOfEnemies, Enemy pigletArmy[],SDL_Renderer* rend, float* enemyScale);

//Chooses how many enemies to spawn dependent to wave number
void chooseWave(int* nrOfEnemies, int* waveNr);
#endif
