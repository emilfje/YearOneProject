#include "lib_menu.h"
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"

int checkClick(ClickableButton *yourButton,int mouse_x,int mouse_y)
{
    if (mouse_x>yourButton->rect.x && mouse_x<(yourButton->rect.x+yourButton->rect.w) && mouse_y>yourButton->rect.y && mouse_y<(yourButton->rect.y+yourButton->rect.h))
    {
        switch(yourButton->state)
        {
            case 0:
            {
                if (!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
                {
                    yourButton->state = 1;
                }
                return MOUSE_OVER;
            }
            case 1:
            {
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    yourButton->state = 2;
                }
                return MOUSE_OVER;
            }
            default:
            {
                if (!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
                {
                    yourButton->state = 0;
                    return MOUSE_CLICK;
                }
                else
                {
                    return MOUSE_OVER;
                }
            }
        }
    }
    else
    {
        yourButton->state = 0;
        return 0;
    }
}

ClickableButton createButton(char directory[], SDL_Renderer* render)
{
    ClickableButton yourButton;
    yourButton.surface = IMG_Load(directory);
    yourButton.texture = SDL_CreateTextureFromSurface(render, yourButton.surface);
    SDL_QueryTexture(yourButton.texture, NULL, NULL, &yourButton.rect.w, &yourButton.rect.h);
    yourButton.state = 0;
    return yourButton;
}


Background createBackground(char directory[], SDL_Renderer* render)
{
    Background yourBackground;
    yourBackground.surface = IMG_Load(directory);
    yourBackground.texture = SDL_CreateTextureFromSurface(render, yourBackground.surface);
    yourBackground.rect.w = WINDOW_WIDTH;
    yourBackground.rect.h = WINDOW_HEIGHT;
    yourBackground.rect.x = 0;
    yourBackground.rect.y = 0;
    return yourBackground;
}

MovingBackground createMovingBg(char directory[], SDL_Renderer* render)
{
    MovingBackground yourBackground;
    yourBackground.surface = IMG_Load(directory);
    yourBackground.texture = SDL_CreateTextureFromSurface(render, yourBackground.surface);
    yourBackground.rect.w = WINDOW_WIDTH*0.75;
    yourBackground.rect.h = WINDOW_HEIGHT;
    yourBackground.rect.x = 0;
    yourBackground.rect.y = 0;
    yourBackground.frame = 0;
    yourBackground.frameTime = 0;
    yourBackground.bgSpriteClips[0].x=0;
    yourBackground.bgSpriteClips[0].y=0;
    yourBackground.bgSpriteClips[0].w=288;
    yourBackground.bgSpriteClips[0].h=216;
    yourBackground.bgSpriteClips[1].x=288;
    yourBackground.bgSpriteClips[1].y=0;
    yourBackground.bgSpriteClips[1].w=288;
    yourBackground.bgSpriteClips[1].h=216;
    yourBackground.bgSpriteClips[2].x=0;
    yourBackground.bgSpriteClips[2].y=216;
    yourBackground.bgSpriteClips[2].w=288;
    yourBackground.bgSpriteClips[2].h=216;
    yourBackground.bgSpriteClips[3].x=288;
    yourBackground.bgSpriteClips[3].y=216;
    yourBackground.bgSpriteClips[3].w=288;
    yourBackground.bgSpriteClips[3].h=216;
    yourBackground.bgSpriteClips[4].x=0;
    yourBackground.bgSpriteClips[4].y=432;
    yourBackground.bgSpriteClips[4].w=288;
    yourBackground.bgSpriteClips[4].h=216;
    yourBackground.bgSpriteClips[5].x=288;
    yourBackground.bgSpriteClips[5].y=432;
    yourBackground.bgSpriteClips[5].w=288;
    yourBackground.bgSpriteClips[5].h=216;
    yourBackground.bgSpriteClips[6].x=576;
    yourBackground.bgSpriteClips[6].y=0;
    yourBackground.bgSpriteClips[6].w=288;
    yourBackground.bgSpriteClips[6].h=216;
    yourBackground.bgSpriteClips[7].x=576;
    yourBackground.bgSpriteClips[7].y=216;
    yourBackground.bgSpriteClips[7].w=288;
    yourBackground.bgSpriteClips[7].h=216;
    yourBackground.bgSpriteClips[8].x=576;
    yourBackground.bgSpriteClips[8].y=432;
    yourBackground.bgSpriteClips[8].w=288;
    yourBackground.bgSpriteClips[8].h=216;
    return yourBackground;
}

void customPlaceTowerAreas(ClickableButton towerArea[], int nrOfTowerAreas, SDL_Renderer* rend)
{
    for (int i = 0; i < nrOfTowerAreas; i++)
    {
        towerArea[i] = createButton("resources/towerArea.png", rend);
    }
    towerArea[0].rect.x = 190;
    towerArea[0].rect.y = 180;
    towerArea[0].rect.w = 280;
    towerArea[0].rect.h = 80;
    towerArea[1].rect.x = 970;
    towerArea[1].rect.y = 180;
    towerArea[1].rect.w = 400;
    towerArea[1].rect.h = 80;
    towerArea[2].rect.x = 190;
    towerArea[2].rect.y = 780;
    towerArea[2].rect.w = 280;
    towerArea[2].rect.h = 80;
    towerArea[3].rect.x = 970;
    towerArea[3].rect.y = 780;
    towerArea[3].rect.w = 280;
    towerArea[3].rect.h = 80;
    towerArea[4].rect.x = 610;
    towerArea[4].rect.y = 60;
    towerArea[4].rect.w = 220;
    towerArea[4].rect.h = 200;
    towerArea[5].rect.x = 610;
    towerArea[5].rect.y = 420;
    towerArea[5].rect.w = 220;
    towerArea[5].rect.h = 200;
    towerArea[6].rect.x = 610;
    towerArea[6].rect.y = 780;
    towerArea[6].rect.w = 220;
    towerArea[6].rect.h = 200;
    towerArea[7].rect.x = 70;
    towerArea[7].rect.y = 420;
    towerArea[7].rect.w = 400;
    towerArea[7].rect.h = 200;
    towerArea[8].rect.x = 970;
    towerArea[8].rect.y = 420;
    towerArea[8].rect.w = 400;
    towerArea[8].rect.h = 200;
}
