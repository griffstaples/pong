
#include "SDL2/SDL.h"
#include "screen.h"

Screen::Screen(SDL_Window *screenWindow, SDL_Renderer *renderer)
{
    window = screenWindow;
    this->renderer = renderer;
};

void Screen::renderScreen(){};