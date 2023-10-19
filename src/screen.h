#pragma once
#include "SDL2/SDL.h"

class Screen
{
protected:
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    Screen(SDL_Window *window, SDL_Renderer *renderer);
    void renderScreen();
};