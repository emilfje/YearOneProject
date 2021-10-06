#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_net.h"
#include "lib_network.h"
#include "lib_activePlayers.h"
#include <stdio.h>
#include <string.h>
#include "SDL_thread.h"
#include "lib_menu.h"
#include "SDL_ttf.h"
#define CONNECTED (1)
#define MAXIPV4CHARS (15)

void networking(Player* player1, Player* opponent, SDL_Renderer* render)
{
    IPaddress ip;
    char serverIP[17];
    //char wrongIP[17] = "Try Again!";
    SDL_Event event;

    TTF_Font* font = TTF_OpenFont("resources/Kapel.ttf", 80);
    SDL_Color fontColor = {0, 0, 0};
    SDL_Surface* inputSurface = TTF_RenderText_Solid(font, serverIP, fontColor);
    SDL_Texture* inputIPtex = SDL_CreateTextureFromSurface(render, inputSurface);

    SDL_Thread *networkThread;
    char text[100];

    SDL_Rect inputRect;
    inputRect.x = 720;
    inputRect.y = 667;
    inputRect.h = 80;
    inputRect.w = 535;
    Background inputWindow = createBackground("resources/serverInput.png", render);

    SDL_RenderCopy(render, inputWindow.texture, NULL, &inputWindow.rect);
    SDL_RenderPresent(render);


    int getInput = 1, nrOfCharacters = 0;
    serverIP[0] = '\0';
    while(getInput)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_RETURN)
            {
                SDLNet_ResolveHost(&ip,serverIP,1234);
                socket = SDLNet_TCP_Open(&ip);
                //If 1 a connection to the server was established
                if(socket)
                {
                    getInput = 0;
                }
                //Connection was not established, reseting string
                else
                {
                    nrOfCharacters = 0;
                    serverIP[0] = '\0';
                    strcat(serverIP, "TRY AGAIN!");
                    getInput = 1;
                    SDL_Delay(100);
                    snprintf(serverIP, sizeof(serverIP), "%s", serverIP);
                    SDL_Surface* inputSurface = TTF_RenderText_Solid(font, serverIP, fontColor);
                    inputIPtex = SDL_CreateTextureFromSurface(render, inputSurface);
                    SDL_FreeSurface(inputSurface);
                    SDL_QueryTexture(inputIPtex, NULL, NULL, &inputRect.w, &inputRect.h);
                    SDL_RenderClear(render);
                    SDL_RenderCopy(render, inputWindow.texture, NULL, &inputWindow.rect);
                    SDL_RenderCopy(render, inputIPtex, NULL, &inputRect);
                    SDL_RenderPresent(render);
                    serverIP[0] = '\0';
                }
            }
            else
            {   //Erase character
                if(event.key.keysym.sym == SDLK_BACKSPACE && nrOfCharacters>0)
                {
                    nrOfCharacters--;
                    serverIP[nrOfCharacters] = '\0';
                    SDL_Delay(90);
                }
                else
                {   //Limit string to maxChars of an IPV4
                    if(nrOfCharacters<MAXIPV4CHARS)
                    {
                        serverIP[nrOfCharacters] = event.key.keysym.sym;
                        nrOfCharacters++;
                        serverIP[nrOfCharacters] = '\0';
                    }
                }
                //Print IPV4-Adress input from user in box
                snprintf(serverIP, sizeof(serverIP), "%s", serverIP);
                SDL_Surface* inputSurface = TTF_RenderText_Solid(font, serverIP, fontColor);
                inputIPtex = SDL_CreateTextureFromSurface(render, inputSurface);
                SDL_FreeSurface(inputSurface);
                SDL_QueryTexture(inputIPtex, NULL, NULL, &inputRect.w, &inputRect.h);
                SDL_RenderClear(render);
                SDL_RenderCopy(render, inputWindow.texture, NULL, &inputWindow.rect);
                SDL_RenderCopy(render, inputIPtex, NULL, &inputRect);
                SDL_RenderPresent(render);
            }
        }
    }

    SDLNet_TCP_Recv(socket, text, sizeof(text)+1);

    printf("%s\n", text);

    SDL_CreateThread(sendData, "sendData", player1);
    SDL_CreateThread(recieveData, "recieveData", opponent);
}

void recieveData(Player *opponent)
{
    int enemlife;
    int enemiesInOPWave;
    float opponenMoney;

    while(CONNECTED)
    {
        SDLNet_TCP_Recv(socket, &enemiesInOPWave, sizeof(int));
        SDLNet_TCP_Recv(socket, &opponenMoney, sizeof(float));
        SDLNet_TCP_Recv(socket, &enemlife, sizeof(int));
        opponent->playerLife = enemlife;
        opponent->enemiesInWave = enemiesInOPWave;
        opponent->money = opponenMoney;
    }
}

void sendData(Player *player1)
{
    int playerlife;
    int enemiesInWave;
    float money;

    while (CONNECTED)
    {
        //Send only if something has changed
        if(playerlife != player1->playerLife || enemiesInWave != player1->enemiesInWave || money != player1->money)
        {
            playerlife = player1->playerLife;
            enemiesInWave = player1->enemiesInWave;
            money = player1->money;
            SDLNet_TCP_Send(socket, &enemiesInWave, sizeof(enemiesInWave));
            SDLNet_TCP_Send(socket, &money, sizeof(money));
            SDLNet_TCP_Send(socket, &playerlife, sizeof(playerlife));
        }
    }
}
