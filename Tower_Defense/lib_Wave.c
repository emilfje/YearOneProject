#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "lib_enemy.h"
#include "SDL.h"
#include "SDL_image.h"
#include "lib_Wave.h"


void createMonsterWave(int* nrOfEnemies,Enemy pigletArmy[],SDL_Renderer* rend, float* enemyScale)
{
    Enemy tempPig;
    for(int q=0; q<*nrOfEnemies; q++)
    {
        tempPig = CreateEnemy(rend);
        tempPig.life = (tempPig.life * *enemyScale);
        pigletArmy[q] = tempPig;
        pigletArmy[q].rect.x += q*200;
        pigletArmy[q].hpBar.x += q*200;
    }
    *enemyScale *= 1.35;
}

void chooseWave(int* nrOfEnemies, int* waveNr)
{
    if(*waveNr == 1)
    {
        *nrOfEnemies = 5;
    }
    else if(*waveNr == 2)
    {
        *nrOfEnemies = 7;
    }
    else if(*waveNr == 3)
    {
        *nrOfEnemies = 10;
    }
    else if (*waveNr == 4)
    {
        *nrOfEnemies = 12;
    }
    else if (*waveNr == 5)
    {
        *nrOfEnemies = 15;
    }
    else if (*waveNr >= 6)
    {
        *nrOfEnemies = 20;
    }
}
