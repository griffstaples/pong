
#include "screen.h"
#include "SDL2/SDL.h"

class HomeScreen : public Screen
{
private:
    SDL_Rect button;
    SDL_Texture *textTexture = nullptr;

public:
    HomeScreen(SDL_Window *screenWindow, SDL_Renderer *renderer);
    ~HomeScreen()
    {
        SDL_DestroyTexture(textTexture);
    }

    void renderScreen();
};