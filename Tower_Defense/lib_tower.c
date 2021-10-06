#include <stdio.h>
#define SDL_MAIN_HANDLED
#include "lib_tower.h"
#include "lib_enemy.h"
#include "pandaAnimation.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define towerShooting (60) // Ändra denna för att justera attack speed!!!
Tower createTower(char directory[], SDL_Renderer* rend, int mouse_x, int mouse_y)
{
    Tower tower1;
    tower1.surface = IMG_Load(directory);
    tower1.tex = SDL_CreateTextureFromSurface(rend, tower1.surface);
    SDL_QueryTexture(tower1.tex, NULL, NULL, &tower1.rect.w, &tower1.rect.h);
    tower1.rect.w =120;
    tower1.rect.h =120;
    tower1.rect.x = mouse_x - tower1.rect.w/2;
    tower1.rect.y = mouse_y - tower1.rect.h/2;
    tower1.range.w = 400;
    tower1.range.h = 400;
    tower1.range.x = tower1.rect.x - (tower1.range.w - tower1.rect.w)/2;
    tower1.range.y = tower1.rect.y - (tower1.range.h - tower1.rect.h)/2;
    tower1.damage = 10;
    tower1.attackSpeed = 30;
    tower1.isShooting = 0;
    tower1.price = 100;
    tower1.flip = SDL_FLIP_NONE;
    tower1.atkSpdUpgrade = 0;
    tower1.damageUpgrade = 0;
    tower1.angle = 0;
    tower1.frame = 1;
    tower1.hasIntersection = 0;
    return tower1;
}
void placeTower(Tower* yourTower, int mouse_x, int mouse_y)
{
    yourTower->rect.x = mouse_x - yourTower->rect.w/2;
    yourTower->rect.y = mouse_y - yourTower->rect.h/2;
    yourTower->range.x = yourTower->rect.x - (yourTower->range.w - yourTower->rect.w)/2;
    yourTower->range.y = yourTower->rect.y - (yourTower->range.h - yourTower->rect.h)/2;
}

void shootEnemy(Tower* tower, Enemy* enemy, Mix_Chunk* towerShootSound)
{
    tower->hasIntersection = 0;
    if(SDL_HasIntersection(&tower->range, &enemy->rect) && tower->attackSpeed>=towerShooting)
    {
        tower->isShooting = 1;
        enemy->life = enemy->life - tower->damage;
        tower->attackSpeed = 0;
        enemy->isHit = 1;
        Mix_PlayChannel(-1, towerShootSound,0);
        tower->hasIntersection = 1;
        calculateAngle(tower, enemy);
    }
    else if(SDL_HasIntersection(&tower->range, &enemy->rect))
    {
        calculateAngle(tower, enemy);
        tower->hasIntersection = 1;
    }

}

void adjustAttackSpeed(Tower* tower)
{
    if(tower->attackSpeed < towerShooting)
    {
        if(tower->atkSpdUpgrade == 1)
        {
            tower->attackSpeed+=2;          //kan behöva göras om till float för bättre scaling
        }
        else
        {
            tower->attackSpeed++;
        }
    }
}

int placeTaken (Tower tower[], int nrOfTowers, int mouse_x, int mouse_y)
{
    if(nrOfTowers == 0)
    {
        return 0;
    }
    for (int i = 0; i < nrOfTowers; i++)
    {
        if(!((mouse_x > tower[i].rect.x+tower[i].rect.w || mouse_x < tower[i].rect.x) || (mouse_y > tower[i].rect.y+tower[i].rect.h || mouse_y < tower[i].rect.y)))
        {
            return i+1;
        }
    }
    return 0;
}

void deleteTower (Tower tower[], int nrOfTowers, int activeTower)
{
    for (int i = activeTower; i< nrOfTowers; i ++)
    {
        tower[i]=tower[i+1];
    }
}

TowerMousePointer createTMP (char directory[], SDL_Renderer* rend)
{
    TowerMousePointer yourMousePointer;
    yourMousePointer.surface = IMG_Load(directory);
    yourMousePointer.texture = SDL_CreateTextureFromSurface(rend, yourMousePointer.surface);
    yourMousePointer.rect.w = 500;
    yourMousePointer.rect.h = 500;
    yourMousePointer.spriteClips[0].x = 0;
    yourMousePointer.spriteClips[0].y = 0;
    yourMousePointer.spriteClips[0].w = 510;
    yourMousePointer.spriteClips[0].h = 510;
    yourMousePointer.spriteClips[1].x = 510;
    yourMousePointer.spriteClips[1].y = 0;
    yourMousePointer.spriteClips[1].w = 510;
    yourMousePointer.spriteClips[1].h = 510;
    yourMousePointer.tryingToPlace = 0;
    return yourMousePointer;
}

void towerUpgradeDamage(SDL_Renderer* rend, Tower* tower)
{
    tower->surface = IMG_Load("resources/bazooka_PandaSprite.png");
    tower->tex = SDL_CreateTextureFromSurface(rend,tower->surface);
}

void towerUpgradeAttackspeed(SDL_Renderer* rend, Tower* tower)
{
    tower->surface = IMG_Load("resources/rifle_Panda_Sprite.png");
    tower->tex = SDL_CreateTextureFromSurface(rend,tower->surface);
}
