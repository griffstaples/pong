
#include "screen.h"
#include "SDL2/SDL.h"

class VictoryScreen : public Screen
{
private:
    SDL_Rect button;
    SDL_Texture *textTexture = nullptr;
    void handleEvents();
    void updateState();
    void renderScreen();
    bool userWon;
    SDL_Event e;

public:
    VictoryScreen(SDL_Window *screenWindow, SDL_Renderer *renderer, ScreenName *currentScreen, bool *quitFlag, bool userWon);
    ~VictoryScreen();
    void run();
};