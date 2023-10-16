
#include "SDL2/SDL.h"

class PongGame
{
private:
    SDL_Window *window = nullptr;
    enum Screen
    {
        HomeScreen,
        PlayScreen,
        VictoryScreen,
    };
    Screen currentScreen = HomeScreen;

public:
    PongGame();
    void runGame();
    void handleUserInteractions();
    void handlePhysics();
    void renderWindow();
};