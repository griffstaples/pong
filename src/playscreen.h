#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "screen.h"
#include "paddle.h"
#include "ball.h"

class PlayScreen : public Screen
{
private:
    Paddle *computerPaddle;
    Paddle *userPaddle;
    Ball *ball;
    TTF_Font *font = nullptr;
    uint8_t userScore = 0;
    uint8_t computerScore = 0;
    SDL_Rect *scoreRectangle = nullptr;
    void handleEvents();
    bool updateState();
    void renderScreen();
    SDL_Event e;

public:
    PlayScreen(SDL_Window *window, SDL_Renderer *renderer, ScreenName *currentScreen, bool *quitFlag);
    ~PlayScreen();
    void renderScore();
    void handleDownMovement();
    void handleUpMovement();
    void handleNoMovement();
    bool run();
};