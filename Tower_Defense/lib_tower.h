#ifndef LIB_TOWER_H_INCLUDED
#define LIB_TOWER_H_INCLUDED
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "lib_enemy.h"

#define NOT_PLACEABLE 1
#define PLACEABLE 2

//Struct containing all necessary items of a tower
typedef struct tower
{
    SDL_Surface* surface;
    SDL_Texture* tex;
    SDL_Rect rect;
    SDL_Rect range;
    SDL_RendererFlip flip;
    int price;
    int isShooting;
    int attackSpeed;
    int damage;
    int atkSpdUpgrade;
    int damageUpgrade;
    int frame;
    double angle;
    int hasIntersection;
}Tower;

typedef struct TowerMousePointers
{
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Rect spriteClips[2];
    int tryingToPlace;
}TowerMousePointer;

//Creates a tower
Tower createTower(char directory[], SDL_Renderer* rend, int mouse_x, int mouse_y);

//�kar attackSpeed med 1 om attackSpped �r mindre �n 60
void adjustAttackSpeed(Tower towers[]);

//Skjuter fienden n�r fienden �n inom range och attackSpeed = 60
void shootEnemy(Tower* tower, Enemy* enemy, Mix_Chunk* towerShootSound);

//placerar ett torn d�r muspekaren �r
void placeTower (Tower* yourTower,int mouse_x,int mouse_y);

//
int placeTaken (Tower tower[], int nrOfTowers, int mouse_x, int mouse_y);

//
void deleteTower (Tower tower[], int nrOfTowers, int activeTower);

//
TowerMousePointer createTMP (char directory[], SDL_Renderer* rend);

//uppgraderar tornets attackspeed och ger tornet en ny sprite
void towerUpgradeAttackspeed(SDL_Renderer* rend, Tower* tower);

//uppgraderar tornets damage och ger tornet en ny sprite
void towerUpgradeDamage(SDL_Renderer* rend, Tower* tower);

#endif // LIB_TOWER_H_INCLUDED
