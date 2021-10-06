#ifndef LIB_GAME_H_INCLUDED
#define LIB_GAME_H_INCLUDED
#include "lib_game.h"
#include <stdio.h>
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include "SDL_net.h"
#include "lib_menu.h"
#include "lib_enemy.h"
#include "lib_tower.h"
#include "lib_activePlayers.h"

#include "pigletAnimation.h"
#include "pandaAnimation.h"

#include "lib_Wave.h"
#include "SDL_mixer.h"
#include "lib_audio.h"
#include "SDL_ttf.h"
#include "lib_network.h"
#define MAX_NR_OF_TOWERS 300
int game();
void gameQuit();
struct input{
SDL_Cursor* hand;
SDL_Cursor* arrow;
SDL_Event eventCheck;
TowerMousePointer pandaMP;
};
struct numbers{
    int timeToPlace;
    int timeToDelete;
    int timeToChange;

    int nrOfTowerAreas;
    int waveNr, lastWave, waveDelay;

    int enemiesLeftInWave;
    int nrOfTowers;
    int activeTower;
    int nrOfRockets;
    int gameMusicPlaying, menuMusicPlaying;
    int pigDead[30]; // nrOfEnemies

    float oldPlayerMoney;
    float oldOpponentMoney;
    int oldEnemies;
    int oldEnemies2;
    int enemyMaxLife[30];
    int activeWindow;
    int quit;
    int youWon;
    int networkRunning;
    int mouse_x, mouse_y;
    int mouseIsOverOne;
    int waitFrame;
    int waitFrameTime;
    float enemyScale;
    int nrOfEnemies;
};
struct buttons{
ClickableButton increaseDamage;
ClickableButton increaseSpeed;
ClickableButton deleteTowerButton;
ClickableButton returnButton;
ClickableButton newTowerButton;
ClickableButton mainMenuButton;
ClickableButton exitButton;
ClickableButton startButton;
ClickableButton quitButton;
};
struct textures{

    SDL_Texture* moneyTexture;

    SDL_Texture* money2Texture;

    SDL_Texture* enemiesTexture;

    SDL_Texture* enemies2Texture;

    SDL_Texture* waitRectTex;

    char charMoney[1000];
    char char2Money[1000];
    char charEnemies[1000];
    char char2Enemies[1000];

    TTF_Font* font;
    SDL_Color fontColor;
};
struct rects{
SDL_Rect moneyRect;
SDL_Rect moneyRect2;
SDL_Rect enemiesRect;
SDL_Rect enemies2Rect;
SDL_Rect waitRect;
};
struct buttons test(SDL_Renderer* rend);
struct textures createTextures(SDL_Renderer* rend,Player* opponent,Player* player1);
struct rects createRects(struct textures texture1);
struct numbers createNumbers( Player* player1, Player* opponent);
struct numbers mainMenu(struct rects* rects1, struct numbers* numbers1, struct input* input1, struct textures* textures1,struct buttons* buttons1, Player* player1,Player* opponent, Mix_Music* menuMusic, SDL_Renderer* rend, Background* mainMenuBg, Background* waitingBg);
void gameRoom(struct rects* rects1,struct numbers* numbers1, struct input* input1, struct textures* textures1,struct buttons* buttons1, Player* player1,Player* opponent,
               Mix_Music* menuMusic, SDL_Renderer* rend, Mix_Music* gameMusic,Tower tower[MAX_NR_OF_TOWERS],ClickableButton towerArea[9],Mix_Chunk* towerShootSound,
               MovingBackground* gameRoomBg,Background hitAnimationn,Mix_Chunk* pigDyingSound,Background guiBg);
//struct input createInput(SDL_Renderer rend);
#endif // LIB_GAME_H_INCLUDED
