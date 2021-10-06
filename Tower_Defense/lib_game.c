#include "lib_game.h"
#include <stdio.h>
#include <stdlib.h>     //
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include "SDL_net.h"
#include "lib_menu.h"
#include "lib_enemy.h"
#include "lib_tower.h"
#include "lib_activePlayers.h"

#include <strings.h> //

#include "pigletAnimation.h"
#include "pandaAnimation.h"

#include "lib_Wave.h"
#include "SDL_mixer.h"
#include "lib_audio.h"
#include "SDL_ttf.h"
#include "lib_network.h"

#define MAX_NR_OF_TOWERS 300
struct input createInput(SDL_Renderer* rend)
{
    struct input output;
    output.hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    output.arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    output.pandaMP = createTMP("resources/pandaMP.png", rend);
    return output;
};
struct numbers createNumbers(Player* player1, Player* opponent){
    struct numbers output;
    int timeToPlace = 0;
    int timeToDelete = 0;
    int timeToChange = 0;
    output.timeToPlace = 0;
    output.timeToDelete = 0;
    output.timeToChange = 0;
    output.nrOfTowerAreas = 9;
    output.waveNr = 1;
    output.lastWave = 0;
    output.waveDelay = 500;
    output.enemiesLeftInWave = 0;
    output.nrOfTowers = 0;
    output.activeTower = 0;
    output.nrOfRockets = 0;
    output.menuMusicPlaying = 0;
    output.gameMusicPlaying = 0;
    output.quit = 0;
    output.youWon = 0;
    output.networkRunning = 0;
    output.activeWindow = START_MENU;
    output.mouseIsOverOne = 0;
    int pigDead[30]; // storlek på array = nrOfEnemies
    int enemyMaxLife[30];
    int mouse_x, mouse_y;
    int mouseIsOverOne = 0;
    int activeWindow = START_MENU;
    float oldPlayerMoney = player1->money;
    float oldOpponentMoney = opponent->money;
    int oldEnemies = player1->enemiesInWave;
    int oldEnemies2 = opponent->enemiesInWave;
    output.oldPlayerMoney = oldPlayerMoney;
    output.oldOpponentMoney = oldOpponentMoney;
    output.oldEnemies = oldEnemies;
    output.oldEnemies2 = oldEnemies2;
    output.waitFrame = 7;
    output.waitFrameTime = 0;
    output.enemyScale = 1;
    return output;
};
struct rects createRects(struct textures texture1)
{
    struct rects output;
    SDL_Rect moneyRect;
    SDL_QueryTexture(texture1.moneyTexture, NULL, NULL, &moneyRect.w, &moneyRect.h);
    moneyRect.x = WINDOW_WIDTH - 160;
    moneyRect.y = WINDOW_HEIGHT/2-85;
    output.moneyRect = moneyRect;
    SDL_Rect moneyRect2;
    SDL_QueryTexture(texture1.money2Texture, NULL, NULL, &moneyRect2.w, &moneyRect2.h);
    moneyRect2.x = WINDOW_WIDTH - 160;
    moneyRect2.y = WINDOW_HEIGHT/4-70;
    output.moneyRect2 = moneyRect2;

    SDL_Rect enemiesRect;
    SDL_QueryTexture(texture1.enemiesTexture, NULL, NULL, &enemiesRect.w, &enemiesRect.h);
    enemiesRect.x = WINDOW_WIDTH - 110;
    enemiesRect.y = WINDOW_HEIGHT/2-183;
    output.enemiesRect = enemiesRect;

    SDL_Rect enemies2Rect;
    SDL_QueryTexture(texture1.enemies2Texture, NULL, NULL, &enemies2Rect.w, &enemies2Rect.h);
    enemies2Rect.x = WINDOW_WIDTH - 110;
    enemies2Rect.y = WINDOW_HEIGHT/4-177;
    output.enemies2Rect = enemies2Rect;

    SDL_Rect waitRect;
    waitRect.x = 850;
    waitRect.y = 675;
    waitRect.h = (96*2);
    waitRect.w = (96*2);
    output.waitRect = waitRect;
    return output;
};
struct textures createTextures(SDL_Renderer* rend,Player* opponent,Player* player1)
{
    char charMoney[1000];
    snprintf(charMoney, sizeof(charMoney), "%f", player1->money); // Omvandlar player.money till en char så att man kan använda den i TTF_RenderText_Solid

    char char2Money[1000];
    snprintf(char2Money, sizeof(char2Money), "%f", opponent->money);

    char charEnemies[1000];
    snprintf(charEnemies, sizeof(charEnemies), "%d", player1->enemiesInWave);

    char char2Enemies[1000];
    snprintf(char2Enemies, sizeof(char2Enemies), "%d", opponent->enemiesInWave);
    struct textures output;
    TTF_Font* font = TTF_OpenFont ("resources/ARCADECLASSIC.ttf",80);
    SDL_Color fontColor = {0, 0, 0};
    SDL_Surface* moneySurface = TTF_RenderText_Solid(font, charMoney, fontColor);

    SDL_Surface* money2Surface = TTF_RenderText_Solid(font, char2Money, fontColor);

    SDL_Surface* enemiesSurface = TTF_RenderText_Solid(font, charEnemies, fontColor);

    SDL_Surface* enemies2Surface = TTF_RenderText_Solid(font, char2Enemies, fontColor);

    SDL_Texture* moneyTexture = SDL_CreateTextureFromSurface(rend, moneySurface);
    output.moneyTexture = moneyTexture;
    SDL_FreeSurface(moneySurface);

    SDL_Texture* money2Texture = SDL_CreateTextureFromSurface(rend, money2Surface);
    output.money2Texture = money2Texture;
    SDL_FreeSurface(money2Surface);

    SDL_Texture* enemiesTexture = SDL_CreateTextureFromSurface(rend, enemiesSurface);
    output.enemiesTexture =enemiesTexture;
    SDL_FreeSurface(enemiesSurface);

    SDL_Texture* enemies2Texture = SDL_CreateTextureFromSurface(rend, enemies2Surface);
    output.enemies2Texture = enemies2Texture;
    SDL_FreeSurface(enemies2Surface);
    strncpy(output.charMoney, charMoney,1000);
    strncpy(output.char2Money, char2Money,1000);
    strncpy(output.charEnemies, charEnemies,1000);
    strncpy(output.char2Enemies, charEnemies,1000);
    output.font = font;
    output.fontColor = fontColor;

    SDL_Surface* waitRectSurface = IMG_Load("resources/grisSprite.png");
    SDL_Texture* waitRectTex = SDL_CreateTextureFromSurface(rend, waitRectSurface);
    output.waitRectTex = waitRectTex;

    return output;
};
struct buttons test(SDL_Renderer* rend)
{
    struct buttons output;
    ClickableButton quitButton = createButton("resources/quit.png", rend);
    quitButton.rect.y = (int) 510 + quitButton.rect.h;
    quitButton.rect.x = (int) WINDOW_WIDTH/2 - quitButton.rect.w/2;
    output.quitButton = quitButton;

    ClickableButton startButton = createButton("resources/start.png", rend);
    startButton.rect.y = (int) 500;
    startButton.rect.x = (int) WINDOW_WIDTH/2 - startButton.rect.w/2;
    output.startButton = startButton;

    ClickableButton exitButton = createButton("resources/exit.png", rend);
    exitButton.rect.y = (int) 0;
    exitButton.rect.x = (int) WINDOW_WIDTH - exitButton.rect.w;
    output.exitButton = exitButton;

    ClickableButton mainMenuButton = createButton("resources/mainMenu.png", rend);
    mainMenuButton.rect.y = startButton.rect.y;
    mainMenuButton.rect.x = startButton.rect.x;
    output.mainMenuButton = mainMenuButton;

    ClickableButton newTowerButton = createButton("resources/newTower.png", rend);
    newTowerButton.rect.x = WINDOW_WIDTH - 460;
    newTowerButton.rect.y = WINDOW_HEIGHT/2+20;
    output.newTowerButton = newTowerButton;
    int timeToPlace = 0;

    ClickableButton returnButton = createButton("resources/return.png", rend);
    returnButton.rect.x = WINDOW_WIDTH - 460;
    returnButton.rect.y = WINDOW_HEIGHT/2+20;
    returnButton.rect.w = 200;
    returnButton.rect.h = 200;
    output.returnButton = returnButton;

    ClickableButton deleteTowerButton = createButton("resources/deleteTower.png", rend);
    deleteTowerButton.rect.x = newTowerButton.rect.x + newTowerButton.rect.w + 20;
    deleteTowerButton.rect.y = newTowerButton.rect.y;
    int timeToDelete = 0;
    output.deleteTowerButton = deleteTowerButton;

    ClickableButton increaseSpeed = createButton("resources/increaseSpeed.png", rend);
    increaseSpeed.rect.x = newTowerButton.rect.x;
    increaseSpeed.rect.y = newTowerButton.rect.y + increaseSpeed.rect.h + 20;
    output.increaseSpeed = increaseSpeed;

    ClickableButton increaseDamage = createButton("resources/increaseDamage.png", rend);
    increaseDamage.rect.x = deleteTowerButton.rect.x;
    increaseDamage.rect.y = increaseSpeed.rect.y;
    output.increaseDamage = increaseDamage;
    return output;
}

int game()
{
    //initiering av grafik
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) !=0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    TTF_Init();
    SDLNet_Init();
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT, 2, 2048);

    Mix_Music *menuMusic = Mix_LoadMUS("resources/soundtrack.mp3");
    Mix_Music *gameMusic = Mix_LoadMUS("resources/the_field_of_dreams.mp3");
    Mix_Chunk *towerShootSound = Mix_LoadWAV("resources/shoot.wav");
    Mix_Chunk *pigDyingSound = Mix_LoadWAV("resources/Pigsnort.wav");

    SDL_Window* win = SDL_CreateWindow("Main menu",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    //skapa en renderare som ordnar hårdvaran
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    loadMedia(rend);
    loadMediaPanda(rend);
    loadMediaPlayerLife(rend);
    loadMediaHpBar(rend);

    //Deklarera och initiera/positionera strcuctar
    Background mainMenuBg = createBackground("resources/Background.png", rend);
    MovingBackground gameRoomBg = createMovingBg("resources/grbSprites.png", rend);
    Background lostGameBg = createBackground("resources/lostGameBg.png", rend);
    Background wonGameBg = createBackground("resources/wonGameBg.png", rend);
    Background waitingBg = createBackground("resources/waiting.png", rend);

    Background guiBg = createBackground("resources/guiBg.png", rend);
    guiBg.rect.x = WINDOW_WIDTH - 480;
    guiBg.rect.w = 480;


    Player *player1 = CreatePlayer(rend);
    Player *opponent = CreatePlayer(rend);
        opponent->rect2.y = WINDOW_HEIGHT/4-70;
        opponent->rect.y = WINDOW_HEIGHT/4-70;
        opponent->playerLife = 0; //för att vänta på server


    struct numbers numbers1 = createNumbers(player1,opponent);
    struct buttons buttons1 = test(rend);
    struct textures texture1 = createTextures(rend,opponent,player1);
    struct rects rects1 = createRects(texture1);
    struct input input1 = createInput(rend);
    ClickableButton towerArea[9];
    customPlaceTowerAreas(towerArea, numbers1.nrOfTowerAreas, rend);

    Background hitAnimation = createBackground("resources/hitAnimation.png", rend);

    hitAnimation.rect.w = 20;
    hitAnimation.rect.w = 20;
    //Player* player1PTR = (Player *) malloc(sizeof(Player));


    Tower tower[MAX_NR_OF_TOWERS];
    //variabler för musposition och utseende


    while(numbers1.quit == 0)
    {
        while (numbers1.activeWindow == START_MENU)
        {
            mainMenu(&rects1,&numbers1,&input1,&texture1,&buttons1,player1,opponent,menuMusic,rend,&mainMenuBg, &waitingBg);
        }
        while (numbers1.activeWindow == GAME_ROOM)
        {
            gameRoom(&rects1,&numbers1,&input1,&texture1,&buttons1,player1,opponent,menuMusic,rend,gameMusic,tower,towerArea,towerShootSound,&gameRoomBg,hitAnimation,pigDyingSound,guiBg);

        }

        while (numbers1.activeWindow == END_MENU)
        {
            SDL_PollEvent(&input1.eventCheck);
            SDL_GetMouseState(&numbers1.mouse_x, &numbers1.mouse_y);
            numbers1.mouseIsOverOne = 0;
            if(numbers1.mouseIsOverOne = checkClick(&buttons1.quitButton, numbers1.mouse_x, numbers1.mouse_y)) //ska endast vara ett "=" här
            {
                if(numbers1.mouseIsOverOne == MOUSE_CLICK)
                {
                    numbers1.quit = 1;
                    break;
                }
                else if (numbers1.mouseIsOverOne == MOUSE_OVER)
                {
                    SDL_SetCursor(input1.hand);
                }
            }

            else if (numbers1.mouseIsOverOne = checkClick(&buttons1.mainMenuButton, numbers1.mouse_x, numbers1.mouse_y)) //ska endast vara ett "=" här
            {
                if(numbers1.mouseIsOverOne == MOUSE_CLICK)
                {
                    numbers1.activeWindow = START_MENU;
                }
                else if (numbers1.mouseIsOverOne == MOUSE_OVER)
                {
                    SDL_SetCursor(input1.hand);
                }
            }
            else
            {
                SDL_SetCursor(input1.arrow);
            }

            SDL_RenderClear(rend);
            if(numbers1.youWon == 1)
            {
                SDL_RenderCopy(rend, wonGameBg.texture, NULL, &wonGameBg.rect);
            }
            else
            {
                SDL_RenderCopy(rend, lostGameBg.texture, NULL, &lostGameBg.rect);
            }
            SDL_RenderCopy(rend, buttons1.mainMenuButton.texture, NULL, &buttons1.mainMenuButton.rect);
            SDL_RenderCopy(rend, buttons1.quitButton.texture, NULL, &buttons1.quitButton.rect);
            SDL_RenderPresent(rend);
            SDL_Delay(1000/60);
        }
    }
    //städa resurser
    SDL_DestroyTexture(buttons1.startButton.texture);
    SDL_DestroyTexture(buttons1.quitButton.texture);
    SDL_DestroyTexture(gameRoomBg.texture);
    SDL_DestroyTexture(mainMenuBg.texture);
    Mix_FreeMusic(menuMusic);
    Mix_FreeMusic(gameMusic);
    Mix_FreeChunk(towerShootSound);
    Mix_FreeChunk(pigDyingSound);
    Mix_CloseAudio();
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    free(player1);
    free(opponent);
    SDLNet_TCP_Close(socket);
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}

struct numbers mainMenu(struct rects* rects1,struct numbers* numbers1,struct  input* input1, struct textures* textures1,struct buttons* buttons1, Player* player1,Player* opponent, Mix_Music* menuMusic, SDL_Renderer* rend, Background* mainMenuBg, Background* waitingBg)
{
    numbers1->youWon = 0;
    playAudio(&numbers1->menuMusicPlaying, menuMusic);
    //eventhantering
    SDL_PollEvent(&input1->eventCheck);
    SDL_GetMouseState(&numbers1->mouse_x, &numbers1->mouse_y);
    numbers1->mouseIsOverOne = 0;
    if(numbers1->mouseIsOverOne = checkClick(&buttons1->quitButton, numbers1->mouse_x, numbers1->mouse_y)) //ska endast vara ett "=" här
    {
        if(numbers1->mouseIsOverOne == MOUSE_CLICK && numbers1->networkRunning != 1)
        {
            numbers1->quit = 1;
            numbers1->activeWindow = 50;
            return;
        }
        else if (numbers1->mouseIsOverOne == MOUSE_OVER && numbers1->networkRunning != 1)
        {
            SDL_SetCursor(input1->hand);
        }
    }
    else if (numbers1->mouseIsOverOne = checkClick(&buttons1->startButton, numbers1->mouse_x, numbers1->mouse_y)) //ska endast vara ett "=" här
    {
        if(numbers1->mouseIsOverOne == MOUSE_CLICK && numbers1->networkRunning != 1)
        {
            player1->playerLife = 3;
            if(!numbers1->networkRunning)
            {
                //Koppla upp mot server
                networking(player1, opponent, rend);
                numbers1->networkRunning = 1;
                SDL_SetCursor(input1->arrow);
            }
            else if (numbers1->networkRunning == 2)
            {
                numbers1->networkRunning = 1;
            }
        }
        else if (numbers1->mouseIsOverOne == MOUSE_OVER && numbers1->networkRunning != 2)
        {
            SDL_SetCursor(input1->hand);
        }
    }
    else
    {
        SDL_SetCursor(input1->arrow);
    }
    if(opponent->playerLife == 3 && numbers1->networkRunning == 1)
    {
        numbers1->activeWindow = GAME_ROOM;
        numbers1->networkRunning = 2;
    }

    //rendering av allt
    SDL_RenderClear(rend);
    if(numbers1->networkRunning == 1)
    {
        if(numbers1->waitFrameTime == 6)
        {
            numbers1->waitFrame--;
            if(numbers1->waitFrame == 3)
            {
                numbers1->waitFrame = 7;
            }
            numbers1->waitFrameTime = 0;
        }
        numbers1->waitFrameTime++;
        SDL_RenderCopy(rend, waitingBg->texture, NULL, &waitingBg->rect);
        SDL_RenderCopyEx(rend, textures1->waitRectTex, &gSpriteClips[numbers1->waitFrame], &rects1->waitRect, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    else if(numbers1->networkRunning != 1)
    {
        SDL_RenderCopy(rend, mainMenuBg->texture, NULL, &mainMenuBg->rect);
        SDL_RenderCopy(rend, buttons1->startButton.texture, NULL, &buttons1->startButton.rect);
        SDL_RenderCopy(rend, buttons1->quitButton.texture, NULL, &buttons1->quitButton.rect);
    }
    SDL_RenderPresent(rend);
    SDL_Delay(1000/60);
    return *numbers1;
}

void gameRoom(struct rects* rects1,struct numbers* numbers1, struct input* input1, struct textures* textures1,struct buttons* buttons1, Player* player1,Player* opponent, Mix_Music* menuMusic, SDL_Renderer* rend, Mix_Music* gameMusic,
              Tower tower[MAX_NR_OF_TOWERS],ClickableButton towerArea[9],Mix_Chunk* towerShootSound,MovingBackground* gameRoomBg,Background hitAnimation,Mix_Chunk* pigDyingSound,Background guiBg)
{
            playAudio(&numbers1->gameMusicPlaying, gameMusic);
            SDL_PollEvent(&input1->eventCheck);
            SDL_GetMouseState(&numbers1->mouse_x, &numbers1->mouse_y);
            input1->pandaMP.tryingToPlace = 0;
            numbers1->mouseIsOverOne = 0;
            if(numbers1->mouseIsOverOne = checkClick(&buttons1->exitButton, numbers1->mouse_x, numbers1->mouse_y)) //ska endast vara ett "=" här
            {
                if(numbers1->mouseIsOverOne == MOUSE_CLICK)
                {
                    player1->playerLife = 0;
                    numbers1->quit = 1;
                    numbers1->activeWindow = 50;
                    return;
                }
                else if (numbers1->mouseIsOverOne == MOUSE_OVER)
                {
                    SDL_SetCursor(input1->hand);
                }
            }
            else if(numbers1->timeToPlace)
            {
                numbers1->mouseIsOverOne = 0;
                if(!placeTaken(tower, numbers1->nrOfTowers, numbers1->mouse_x, numbers1->mouse_y))
                {
                    for(int i =0; i< numbers1->nrOfTowerAreas; i++)
                    {
                        if (numbers1->mouseIsOverOne = checkClick(&towerArea[i], numbers1->mouse_x, numbers1->mouse_y))
                        {
                            if (numbers1->mouseIsOverOne == MOUSE_CLICK)
                            {
                                int j = numbers1->nrOfTowers;
                                tower[numbers1->nrOfTowers] = createTower("resources/pandaSprite.png",rend, numbers1->mouse_x, numbers1->mouse_y);
                                numbers1->nrOfTowers++;
                                numbers1->timeToPlace = 0;
                                input1->pandaMP.tryingToPlace = 0;
                                player1->money -= tower[j].price;
                                break;
                            }
                            else if (numbers1->mouseIsOverOne == MOUSE_OVER)
                            {
                                SDL_SetCursor(input1->hand);
                                numbers1->mouseIsOverOne = 1;
                                input1->pandaMP.tryingToPlace = PLACEABLE;
                                break;
                            }
                        }
                        else if (numbers1->mouseIsOverOne = checkClick(&buttons1->returnButton, numbers1->mouse_x, numbers1->mouse_y)) //ska endast vara ett "=" här
                        {
                            if(numbers1->mouseIsOverOne == MOUSE_CLICK)
                            {
                                numbers1->timeToPlace = 0;
                            }
                            else if (numbers1->mouseIsOverOne == MOUSE_OVER)
                            {
                                SDL_SetCursor(input1->hand);
                                numbers1->mouseIsOverOne = 1;
                            }
                        }
                    }
                }
                if (numbers1->mouseIsOverOne != 1)
                {
                    SDL_SetCursor(input1->arrow);
                    input1->pandaMP.tryingToPlace = NOT_PLACEABLE;
                }
            }
            else if(numbers1->timeToChange)
            {
                if(numbers1->mouseIsOverOne =checkClick(&buttons1->deleteTowerButton, numbers1->mouse_x, numbers1->mouse_y))
                {
                    if (numbers1->mouseIsOverOne == MOUSE_CLICK)
                    {
                        player1->money += tower[numbers1->nrOfTowers-1].price*0.75;
                        deleteTower(tower, numbers1->nrOfTowers, numbers1->activeTower);
                        numbers1->nrOfTowers--;
                        numbers1->timeToChange = 0;
                    }
                    else if (numbers1->mouseIsOverOne == MOUSE_OVER)
                    {
                        SDL_SetCursor(input1->hand);
                    }
                }
                else if(numbers1->mouseIsOverOne =checkClick(&buttons1->increaseSpeed, numbers1->mouse_x, numbers1->mouse_y))
                {
                    if (numbers1->mouseIsOverOne == MOUSE_CLICK)
                    {
                        if(player1->money >= 200 && tower[numbers1->activeTower].atkSpdUpgrade != 1 && tower[numbers1->activeTower].damageUpgrade !=1)
                        {
                            //här ska skottfrekvensen ökas
                            tower[numbers1->activeTower].atkSpdUpgrade = 1;
                            tower[numbers1->activeTower].damage +=5;
                            towerUpgradeAttackspeed(rend, &tower[numbers1->activeTower]);
                            player1->money -= 200;
                            numbers1->timeToChange = 0;
                        }
                    }
                    else if (numbers1->mouseIsOverOne == MOUSE_OVER)
                    {
                        SDL_SetCursor(input1->hand);
                    }
                }
                else if(numbers1->mouseIsOverOne =checkClick(&buttons1->increaseDamage, numbers1->mouse_x, numbers1->mouse_y))
                {
                    if (numbers1->mouseIsOverOne == MOUSE_CLICK)
                    {
                        if(player1->money >= 200 && tower[numbers1->activeTower].damageUpgrade != 1 && tower[numbers1->activeTower].atkSpdUpgrade != 1)
                        {
                            //här ska skadan ökas
                            tower[numbers1->activeTower].damageUpgrade = 1;
                            tower[numbers1->activeTower].damage += 15;
                            towerUpgradeDamage(rend, &tower[numbers1->activeTower]);
                            player1->money -= 200;
                            numbers1->timeToChange = 0;
                        }
                    }
                    else if (numbers1->mouseIsOverOne == MOUSE_OVER)
                    {
                        SDL_SetCursor(input1->hand);
                    }
                }
                else if (numbers1->mouseIsOverOne = checkClick(&buttons1->returnButton, numbers1->mouse_x, numbers1->mouse_y)) //ska endast vara ett "=" här
                {
                    if(numbers1->mouseIsOverOne == MOUSE_CLICK)
                    {
                        numbers1->timeToChange = 0;
                    }
                    else if (numbers1->mouseIsOverOne == MOUSE_OVER)
                    {
                        SDL_SetCursor(input1->hand);
                        numbers1->mouseIsOverOne = 1;
                    }
                }
                else
                {
                    SDL_SetCursor(input1->arrow);
                }
            }

            else
            {
                numbers1->mouseIsOverOne = 0;
                if(numbers1->activeTower = placeTaken(tower, numbers1->nrOfTowers, numbers1->mouse_x, numbers1->mouse_y))//ska endast vara ett "=" tecken
                {
                    SDL_SetCursor(input1->hand);
                    numbers1->mouseIsOverOne = 1;
                    numbers1->activeTower --; //den returnerar tornet +1
                    for(int i =0; i< numbers1->nrOfTowerAreas; i++)
                    {
                        if (checkClick(&towerArea[i], numbers1->mouse_x, numbers1->mouse_y) == MOUSE_CLICK)
                        {
                            numbers1->timeToChange = 1;
                            SDL_SetCursor(input1->arrow);
                        }
                    }
                }
                else if(numbers1->mouseIsOverOne = checkClick(&buttons1->newTowerButton, numbers1->mouse_x, numbers1->mouse_y)) //ska endast vara ett "=" här
                {
                    if (numbers1->mouseIsOverOne == MOUSE_CLICK)
                    {
                        if(player1->money >= 100)
                        {
                            numbers1->timeToPlace = 1;
                            return;
                        }
                    }
                    else if (numbers1->mouseIsOverOne == MOUSE_OVER)
                    {
                        SDL_SetCursor(input1->hand);
                    }
                }
                if( input1->eventCheck.type == SDL_KEYDOWN )
                {
                    //Select which wave to send
                    switch( input1->eventCheck.key.keysym.sym )
                    {
                       case SDLK_ESCAPE:
                            SDL_RenderClear(rend);
                            numbers1->waveNr=1;
                            player1->playerLife = 3;
                            player1->money = 100;
                            opponent->playerLife = 0;
                            numbers1->nrOfTowers = 0;
                            numbers1->enemiesLeftInWave = 0;
                            numbers1->activeWindow = START_MENU;
                            Mix_HaltMusic();
                            numbers1->gameMusicPlaying = 0;
                            numbers1->menuMusicPlaying = 0;
                            break;
                    }
                }
                if(numbers1->mouseIsOverOne != 1)
                {
                    SDL_SetCursor(input1->arrow);
                }
            }

            //gameplayberäkningar
            if(numbers1->waveDelay==0)
            {
                if (numbers1->enemiesLeftInWave == -1)                //Auto spawn next wave if last wave has perished
                {
                    chooseWave(&numbers1->nrOfEnemies, &numbers1->waveNr);
                    createMonsterWave(&numbers1->nrOfEnemies, pigletArmy,rend,&numbers1->enemyScale);
                    numbers1->enemiesLeftInWave = numbers1->nrOfEnemies;
                    player1->enemiesInWave = numbers1->nrOfEnemies;
                    numbers1->waveNr++;
                    for(int i=0;i<numbers1->nrOfEnemies;i++)
                    {
                        numbers1->pigDead[i]=0;
                        numbers1->enemyMaxLife[i]=pigletArmy[i].life;
                    }
                }
            }
            //delayclock
            else
            {
                numbers1->waveDelay--;
            }
            for (int j=0; j<numbers1->nrOfTowers; j++)
            {
                for(int i=0; i<numbers1->enemiesLeftInWave; i++)                    //Shoot first in line enemy
                {
                    if (pigletArmy[i].life>0)                       //Shot only at living enemies
                    {
                        shootEnemy(&tower[j], &pigletArmy[i], towerShootSound);

                    }
                    if(tower[j].hasIntersection !=0)
                    {
                        break;
                    }
                }
            }
            //Adjust the firing speed of towers
            for (int i=0; i<numbers1->nrOfTowers; i++)
            {
                adjustAttackSpeed(&tower[i]);
            }

            for(int j=0; j<numbers1->enemiesLeftInWave; j++)                    //Move all living enemies
            {
                if(pigletArmy[j].life >= 0)
                {
                    animateStruct(&pigletArmy[j]);
                }
            }

            for (int i=0; i<numbers1->enemiesLeftInWave;i++)                    //checks if an enemy has died
            {
                if(pigletArmy[i].life <=0)
                {                                               //If enemy[i] has died give player money and despawn enemy
                    player1->money += pigletArmy[i].value;
                    for(i;i<numbers1->enemiesLeftInWave;i++)
                    {
                        pigletArmy[i] = pigletArmy[i+1];
                    }
                    player1->enemiesInWave--;
                    numbers1->enemiesLeftInWave--;                        //decrease the amount of enemies left in wave variable
                }
                if(pigletArmy[i].rect.y == 290 && pigletArmy[i].rect.x >=1440 && pigletArmy[i].life>0)
                {                                               //If an enemy has made it through, damage player and despawn enemy
                    player1->playerLife--;

                    for(i;i<numbers1->enemiesLeftInWave;i++)
                    {
                        pigletArmy[i] = pigletArmy[i+1];
                    }
                    numbers1->enemiesLeftInWave--;
                    player1->enemiesInWave--;
                }
            }
            for(int i=0; i<numbers1->enemiesLeftInWave; i++)
            {
                pathFinding(&pigletArmy[i]);
            }

            if(player1->enemiesInWave <= 0 && opponent->enemiesInWave <= 0 && numbers1->enemiesLeftInWave != -1) //Checks if all enemies in current wave are dead
            {                                                   //If all are dead gives player money and set int to -1
                player1->money += 150;
                numbers1->enemiesLeftInWave--;
                numbers1->waveDelay=250;
                for(int i=0;i<numbers1->nrOfTowers;i++)
                {
                    tower[i].angle = 0;
                    tower[i].frame = 1;
                }
            }

            if(player1->playerLife <=0 || opponent->playerLife <=0)
            {
                if(opponent->playerLife<=0)
                {
                    numbers1->youWon =1;
                }
                SDL_RenderClear(rend);
                numbers1->waveNr=1;
                player1->money = 100;
                opponent->playerLife = 0;
                player1->playerLife = 0;
                player1->enemiesInWave = 0;
                numbers1->nrOfTowers = 0;
                numbers1->enemiesLeftInWave = 0;
                numbers1->waveDelay = 500;
                numbers1->activeWindow = END_MENU;
                numbers1->enemyScale = 1;
                Mix_HaltMusic();
                numbers1->gameMusicPlaying = 0;
                numbers1->menuMusicPlaying = 0;
            }
            if(player1->money != numbers1->oldPlayerMoney)
            {
                snprintf(textures1->charMoney, sizeof(textures1->charMoney), "%.0f", player1->money);
                SDL_Surface* moneySurface = TTF_RenderText_Solid(textures1->font, textures1->charMoney, textures1->fontColor);
                textures1->moneyTexture = SDL_CreateTextureFromSurface(rend, moneySurface);
                SDL_FreeSurface(moneySurface);
                SDL_QueryTexture(textures1->moneyTexture, NULL, NULL, &rects1->moneyRect.w, &rects1->moneyRect.h);
                numbers1->oldPlayerMoney = player1->money;
            }
            if(opponent->money != numbers1->oldOpponentMoney)
            {
                snprintf(textures1->char2Money, sizeof(textures1->char2Money), "%.0f", opponent->money);
                SDL_Surface* money2Surface = TTF_RenderText_Solid(textures1->font, textures1->char2Money, textures1->fontColor);
                textures1->money2Texture = SDL_CreateTextureFromSurface(rend, money2Surface);
                SDL_FreeSurface(money2Surface);
                SDL_QueryTexture(textures1->money2Texture, NULL, NULL, &rects1->moneyRect2.w, &rects1->moneyRect2.h);
                numbers1->oldOpponentMoney = opponent->money;
            }
            if(player1->enemiesInWave != numbers1->oldEnemies)
            {
                snprintf(textures1->charEnemies, sizeof(textures1->charEnemies), "%.d", player1->enemiesInWave);
                SDL_Surface* enemiesSurface = TTF_RenderText_Solid(textures1->font, textures1->charEnemies, textures1->fontColor);
                textures1->enemiesTexture = SDL_CreateTextureFromSurface(rend, enemiesSurface);
                SDL_FreeSurface(enemiesSurface);
                SDL_QueryTexture(textures1->enemiesTexture, NULL, NULL, &rects1->enemiesRect.w, &rects1->enemiesRect.h);
                numbers1->oldEnemies = player1->enemiesInWave;
            }
            if(opponent->enemiesInWave != numbers1->oldEnemies2)
            {
                snprintf(textures1->char2Enemies, sizeof(textures1->char2Enemies), "%.d", opponent->enemiesInWave);
                SDL_Surface* enemies2Surface = TTF_RenderText_Solid(textures1->font, textures1->char2Enemies, textures1->fontColor);
                textures1->enemies2Texture = SDL_CreateTextureFromSurface(rend, enemies2Surface);
                SDL_FreeSurface(enemies2Surface);
                SDL_QueryTexture(textures1->enemies2Texture, NULL, NULL, &rects1->enemies2Rect.w, &rects1->enemies2Rect.h);
                numbers1->oldEnemies2 = opponent->enemiesInWave;
            }

            //Update health bar of enemies
            updateHpBar(pigletArmy, numbers1->enemiesLeftInWave, numbers1->enemyMaxLife);

            //rendering av allt
            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, gameRoomBg->texture, &gameRoomBg->bgSpriteClips[gameRoomBg->frame], &gameRoomBg->rect);
            gameRoomBg->frameTime++;
            if(gameRoomBg->frameTime==5)
            {
                gameRoomBg->frame++;
                gameRoomBg->frameTime =0;
            }
            if (gameRoomBg->frame == 9)
            {
                gameRoomBg->frame =0;
            }

            for(int i=0; i<numbers1->enemiesLeftInWave; i++)
            {
                if(pigletArmy[i].life>0)
                {
                    SDL_RenderCopyEx(rend, pigletArmy[i].texture, &gSpriteClips[pigletArmy[i].frame], &pigletArmy[i].rect , 0, NULL, pigletArmy[i].flip);
                    if(pigletArmy[i].hpBar.w <= 100 && pigletArmy[i].hpBar.w >= 67)
                    {
                        SDL_RenderCopyEx(rend, pigletArmy[i].texture2, &hSpriteClips[0], &pigletArmy[i].hpBar, 0, NULL, SDL_FLIP_NONE);
                    }
                    else if(pigletArmy[i].hpBar.w <= 66 && pigletArmy[i].hpBar.w >= 33)
                    {
                        SDL_RenderCopyEx(rend, pigletArmy[i].texture2, &hSpriteClips[1], &pigletArmy[i].hpBar, 0, NULL, SDL_FLIP_NONE);
                    }
                    else if(pigletArmy[i].hpBar.w <= 32 && pigletArmy[i].hpBar.w >= 0)
                    {
                        SDL_RenderCopyEx(rend, pigletArmy[i].texture2, &hSpriteClips[2], &pigletArmy[i].hpBar, 0, NULL, SDL_FLIP_NONE);
                    }
                }
                if(pigletArmy[i].isHit)
                {
                    SDL_RenderCopy(rend, hitAnimation.texture, NULL, &pigletArmy[i].rect);
                    pigletArmy[i].isHit = 0;
                }
                if(pigletArmy[i].life<=0 && numbers1->pigDead[i]!=1)
                {
                    Mix_PlayChannel(-1, pigDyingSound,0);
                    numbers1->pigDead[i] = 1;
                }
            }

            SDL_RenderCopy(rend, guiBg.texture, NULL, &guiBg.rect);

            if(numbers1->timeToPlace)
            {
                SDL_RenderCopy(rend, buttons1->returnButton.texture, NULL, &buttons1->returnButton.rect);
            }
            else if(numbers1->timeToChange)
            {
                SDL_RenderCopy(rend, buttons1->deleteTowerButton.texture, NULL, &buttons1->deleteTowerButton.rect);
                SDL_RenderCopy(rend, buttons1->returnButton.texture, NULL, &buttons1->returnButton.rect);
                if(player1->money >=200 && !tower[numbers1->activeTower].atkSpdUpgrade && !tower[numbers1->activeTower].damageUpgrade)
                {
                    SDL_RenderCopy(rend, buttons1->increaseSpeed.texture, NULL, &buttons1->increaseSpeed.rect);
                    SDL_RenderCopy(rend, buttons1->increaseDamage.texture, NULL, &buttons1->increaseDamage.rect);
                }
            }
            else if(player1->money >=100)
            {
                SDL_RenderCopy(rend, buttons1->newTowerButton.texture, NULL, &buttons1->newTowerButton.rect);
            }

            for(int i=0; i<numbers1->nrOfTowers; i++)
            {
                if(tower[i].isShooting == 0)
                {
                    SDL_RenderCopyEx(rend, tower[i].tex, &pSpriteClips[tower[i].frame], &tower[i].rect, tower[i].angle, NULL, tower[i].flip);
                }
                else
                {
                    SDL_RenderCopyEx(rend, tower[i].tex, &pSpriteClips[tower[i].frame-1], &tower[i].rect, tower[i].angle, NULL, tower[i].flip);
                    tower[i].isShooting++;
                    if(tower[i].isShooting == 10)
                    {
                        tower[i].isShooting = 0;
                    }
                }
            }

            //Render player + opponents life
            SDL_RenderCopyEx(rend, player1->texture, &lSpriteClips[player1->playerLife-1], &player1->rect, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(rend, opponent->texture, &lSpriteClips[opponent->playerLife-1], &opponent->rect, 0, NULL, SDL_FLIP_NONE);

            //Render players money, and number of enemies in wave
            SDL_RenderCopy(rend, player1->texture2, NULL, &player1->rect2);
            SDL_RenderCopy(rend, textures1->moneyTexture, NULL, &rects1->moneyRect);
            SDL_RenderCopy(rend, textures1->enemiesTexture, NULL, &rects1->enemiesRect);

            SDL_RenderCopy(rend, opponent->texture2, NULL, &opponent->rect2);
            SDL_RenderCopy(rend, textures1->money2Texture, NULL, &rects1->moneyRect2);
            SDL_RenderCopy(rend, textures1->enemies2Texture, NULL, &rects1->enemies2Rect);

            SDL_RenderCopy(rend, buttons1->exitButton.texture, NULL, &buttons1->exitButton.rect);
            SDL_RenderCopy(rend, buttons1->exitButton.texture, NULL, &buttons1->exitButton.rect);

            if (input1->pandaMP.tryingToPlace)
            {
                input1->pandaMP.rect.x = numbers1->mouse_x - input1->pandaMP.rect.w/2;
                input1->pandaMP.rect.y = numbers1->mouse_y - input1->pandaMP.rect.h/2;
                SDL_RenderCopyEx(rend, input1->pandaMP.texture, &input1->pandaMP.spriteClips[input1->pandaMP.tryingToPlace-1] , &input1->pandaMP.rect, 0, NULL, SDL_FLIP_NONE);
            }
            SDL_RenderPresent(rend);
            SDL_Delay(1000/60);
            return;
        }



