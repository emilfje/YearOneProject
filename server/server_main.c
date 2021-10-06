#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_net.h"
#include <stdio.h>
#include <string.h>
#define CONNECTED (1)
#define SERVER_FULL (3)

//struct innehållande data som ska ändras av main samt tråd
typedef struct ServerStructs
{
    TCPsocket client1;
    TCPsocket client2;
} ServerStruct;
//tråd som skickar och tar emot data från spelare 2 till spelare 1
void client2Thread(ServerStruct *serverStructPTR);


int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();

    IPaddress ip;
    SDLNet_ResolveHost(&ip,NULL,1234); //hämtar datorns ip-adress
    TCPsocket server = SDLNet_TCP_Open(&ip);
    ServerStruct *serverStructPTR = malloc(sizeof(ServerStruct));
    int nextPlayer = 1;
    char text[] = "You are connected as player one.\n";
    char text2[] = "You are connected as player two.\n";

    while(CONNECTED)
    {
        if(nextPlayer == 1)
        {
            serverStructPTR->client1=SDLNet_TCP_Accept(server);
            if(serverStructPTR->client1)
            {
                printf("Player one is connected.\n");
                SDLNet_TCP_Send (serverStructPTR->client1, text, strlen(text)+1);
                nextPlayer++;
            }
        }
        else if(nextPlayer == 2)
        {
            serverStructPTR->client2=SDLNet_TCP_Accept(server);
            if(serverStructPTR->client2)
            {
                printf("Player two is connected.\n");
                SDLNet_TCP_Send (serverStructPTR->client2, text2, strlen(text2)+1);
                SDL_CreateThread(client2Thread, "client2Thread", serverStructPTR);
                nextPlayer++;
            }
        }
        else if(nextPlayer==SERVER_FULL)
        {
            int life, enemiesInWave;
            float money;

            while (CONNECTED) //hämta data från spelare 2 och skicka till spelare 1
            {
                SDLNet_TCP_Recv(serverStructPTR->client1, &enemiesInWave , sizeof(int));
                SDLNet_TCP_Recv(serverStructPTR->client1, &money, sizeof(float));
                SDLNet_TCP_Recv(serverStructPTR->client1, &life, sizeof(int));
                SDLNet_TCP_Send(serverStructPTR->client2, &enemiesInWave, sizeof(enemiesInWave));
                SDLNet_TCP_Send(serverStructPTR->client2, &money, sizeof(money));
                SDLNet_TCP_Send(serverStructPTR->client2, &life, sizeof(life));
            }
        }
    }
    SDLNet_TCP_Close(server);
    SDLNet_Quit();
    SDL_Quit();
}

void client2Thread(ServerStruct *serverStructPTR)
{
    int life, enemiesInWave;
    float money;
    while (CONNECTED) //hämta data från spelare 1 och skicka till spelare 2
    {
        SDLNet_TCP_Recv(serverStructPTR->client2, &enemiesInWave , sizeof(int));
        SDLNet_TCP_Recv(serverStructPTR->client2, &money, sizeof(float));
        SDLNet_TCP_Recv(serverStructPTR->client2, &life, sizeof(int));
        SDLNet_TCP_Send(serverStructPTR->client1, &enemiesInWave, sizeof(enemiesInWave));
        SDLNet_TCP_Send(serverStructPTR->client1, &money, sizeof(money));
        SDLNet_TCP_Send(serverStructPTR->client1, &life, sizeof(life));
    }
}

