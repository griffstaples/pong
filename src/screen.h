#pragma once
#include "SDL2/SDL.h"
#include "pong_types.h"

class Screen
{
protected:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    ScreenName *currentScreen;
    bool *quitFlag;

public:
    Screen(SDL_Window *window, SDL_Renderer *renderer, ScreenName *currentScreen, bool *quitFlag);
};