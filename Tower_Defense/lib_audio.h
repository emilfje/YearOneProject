#include <stdio.h>
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_mixer.h"
#ifndef LIB_AUDIO_H_INCLUDED
#define LIB_AUDIO_H_INCLUDED

//Plays a song and makes sure the song doesn't restart in the loop
void playAudio(int *musicPlaying, Mix_Music* menuMusic);


#endif // LIB_AUDIO_H_INCLUDED
