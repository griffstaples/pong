
#include "SDL2/SDL.h"
#include "homescreen.h"
#include "playscreen.h"
#include "victoryscreen.h"
#include "pong_types.h"

class PongGame
{
private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    ScreenName currentScreen;
    ScreenName *currentScreenP = &currentScreen;
    bool quitFlag;
    bool *quitFlagP = &quitFlag;
    bool userWon;

public:
    PongGame();
    void runGame();
    ~PongGame();
};