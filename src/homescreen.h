
#include "screen.h"
#include "SDL2/SDL.h"

class HomeScreen : public Screen
{
private:
    Button *playButton;

public:
    HomeScreen(SDL_Window *screenWindow);
    void renderScreen();
};