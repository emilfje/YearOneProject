#include <stdio.h>
#define SDL_MAIN_HANDLED
#include "lib_audio.h"
#include "SDL.h"
#include "SDL_mixer.h"

void playAudio(int *musicPlaying, Mix_Music* music)
{
    if(*musicPlaying == 0)
    {
        Mix_PlayMusic(music, -1);
        *musicPlaying = 1;
    }
}

