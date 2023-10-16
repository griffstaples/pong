
#include "SDL2/SDL.h"

class Screen
{
protected:
    SDL_Window *window;

public:
    Screen(SDL_Window *window);
    void renderScreen();
};