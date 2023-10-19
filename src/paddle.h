#include <cstdint>
#include <SDL2/SDL.h>

class Paddle
{
private:
    float x; // top left x pixel
    float y; // top left y pixel
    uint16_t width = 20;
    uint16_t height = 40;
    float velocityY = 0;
    SDL_Color color = {255, 255, 255, 255};

public:
    Paddle(float x, float y, uint16_t width, uint16_t height, float velocityY);
    float getX();
    float getY();
    void setX(float x);
    void setY(float y);
    float getVelocityY();
    void setVelocityY(float velocityY);
    uint16_t getHeight();
    void render(SDL_Renderer *renderer);
};