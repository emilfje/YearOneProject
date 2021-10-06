#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"

#define MOUSE_OVER 1
#define MOUSE_CLICK 2

#define WINDOW_WIDTH (1920)
#define WINDOW_HEIGHT (1080)

#define START_MENU 0
#define GAME_ROOM 1
#define END_MENU 2


//a button for interface
typedef struct ClickableButtons
{
    SDL_Rect rect;
    int state;
    SDL_Surface* surface;
    SDL_Texture* texture;
} ClickableButton;
//a background to be rendered berfore anything else
typedef struct Backgrounds
{
    SDL_Rect rect;
    SDL_Surface* surface;
    SDL_Texture* texture;
} Background;
//a background that's animated
typedef struct MovingBackgrounds
{
    SDL_Rect bgSpriteClips[9];
    SDL_Rect rect;
    SDL_Surface* surface;
    SDL_Texture* texture;
    int frame;
    int frameTime;
} MovingBackground;

//checks if the button is pressed or if the mouse is placed over the button
int checkClick(ClickableButton *yourButton,int mouse_x, int mouse_y);

//returns a button made of the image in the directory passed with the function
ClickableButton createButton(char directory[], SDL_Renderer* render);

//returns a background with the image in the directory passed with the function
Background createBackground(char directory[], SDL_Renderer* render);

//creates an animated background with the images in a 3X3 spritesheet passed with the function
MovingBackground createMovingBg(char directory[], SDL_Renderer* render);
//places buttons where you can place towers, specifically for the map in the game
void customPlaceTowerAreas(ClickableButton towerArea[], int nrOfTowerAreas, SDL_Renderer* rend);
#endif
