
#include "screen.h"
#include "SDL2/SDL.h"

class HomeScreen : public Screen
{
private:
    SDL_Rect button;
    SDL_Texture *textTexture = nullptr;
    void handleEvents();
    void updateState();
    void renderScreen();
    SDL_Event e;

public:
    HomeScreen(SDL_Window *screenWindow, SDL_Renderer *renderer, ScreenName *currentScreen, bool *quitFlag);
    ~HomeScreen();
    void run();
};