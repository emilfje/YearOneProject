#include "SDL.h"
#include "SDL_image.h"
#include "lib_path.h"
#include "lib_enemy.h"

void pathFinding(Enemy* piglet)
{
    //printf("pig y: %d\n",piglet->rect.y);
    if(piglet->rect.x <= 840 && piglet->rect.y == 61 && piglet->numberOfTurns == 0)
    {
        piglet->directions = 1;
        piglet->rect.x = 840;
        piglet->numberOfTurns++;
    }
    else if(piglet->rect.x == 840 && (piglet->rect.y + piglet->rect.h) >= 1020 && piglet->numberOfTurns == 1)
    {
        piglet->rect.y = (1020 - piglet->rect.h);
        piglet->directions = 3;
        piglet->numberOfTurns++;
    }
    else if((piglet->rect.x + piglet->rect.w) >= 1380 && (piglet->rect.y + piglet->rect.h) == 1020 && piglet->numberOfTurns == 2)
    {
        piglet->rect.x = (1380 - piglet->rect.w);
        piglet->directions = 0;
        piglet->numberOfTurns++;
    }
    else if((piglet->rect.x + piglet->rect.w) == 1380 && piglet->rect.y <= 660 && piglet->numberOfTurns == 3)
    {
        piglet->rect.y = 660;
        piglet->directions = 2;
        piglet->numberOfTurns++;
    }
    else if(piglet->rect.x <= 60 && piglet->rect.y == 660 && piglet->numberOfTurns == 4)
    {
        piglet->rect.x = 60;
        piglet->directions = 1;
        piglet->numberOfTurns++;
    }
    else if(piglet->rect.x == 60 && (piglet->rect.y + piglet->rect.h) >= 1020 && piglet->numberOfTurns == 5)
    {
        piglet->rect.y = (1020 - piglet->rect.h);
        piglet->directions = 3;
        piglet->numberOfTurns++;
    }
    else if((piglet->rect.x + piglet->rect.w) >= 600 && (piglet->rect.y + piglet->rect.h) == 1020 && piglet->numberOfTurns == 6)
    {
        piglet->rect.x = (600 - piglet->rect.w);
        piglet->directions = 0;
        piglet->numberOfTurns++;
    }
    else if((piglet->rect.x + piglet->rect.w) == 600 && piglet->rect.y <= 60 && piglet->numberOfTurns == 7)
    {
        piglet->rect.y = 60;
        piglet->directions = 2;
        piglet->numberOfTurns++;
    }
    else if(piglet->rect.x <= 60 && piglet->rect.y == 60 && piglet->numberOfTurns == 8)
    {
        piglet->rect.x = 60;
        piglet->directions = 1;
        piglet->numberOfTurns++;
    }
    else if(piglet->rect.x == 60 && (piglet->rect.y + piglet->rect.h) >= 390 && piglet->numberOfTurns == 9)
    {
        piglet->rect.y = (390 - piglet->rect.h);
        piglet->directions = 3;
        piglet->numberOfTurns++;
    }
}
