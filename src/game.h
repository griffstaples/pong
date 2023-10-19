
#include "SDL2/SDL.h"
#include "homescreen.h"
#include "playscreen.h"

class PongGame
{
private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    enum ScreenName
    {
        Home,
        Play,
        Victory,
    };
    ScreenName currentScreen = Home;
    HomeScreen *homeScreen = nullptr;
    PlayScreen *playScreen = nullptr;

public:
    PongGame();
    void runGame();
    void handleUserInteractions();
    void handlePhysics();
    void renderWindow();
    ~PongGame()
    {
        delete homeScreen;
    };
};