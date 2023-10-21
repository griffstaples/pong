
#include "SDL2/SDL.h"
#include "screen.h"

Screen::Screen(SDL_Window *window, SDL_Renderer *renderer, ScreenName *screen, bool *quitFlag)
{
    this->window = window;
    this->renderer = renderer;
    this->currentScreen = screen;
    this->quitFlag = quitFlag;
};
