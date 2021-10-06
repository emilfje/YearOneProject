#ifndef LIB_NETWORK_H_INCLUDED
#define LIB_NETWORK_H_INCLUDED
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_net.h"
#include "lib_activePlayers.h"

void networking(Player* player1, Player* opponent, SDL_Renderer* render);
void sendData(Player *player1);
void recieveData(Player *opponent);
TCPsocket socket;

#endif

