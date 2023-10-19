#include <SDL2/SDL.h>
#include <cstdint>

class Ball
{
private:
    uint16_t x;
    uint16_t y;
    uint16_t radius;
    float velocityX;
    float velocityY;
    SDL_Color color = {255, 255, 255, 255};

public:
    Ball(uint16_t x, uint16_t y, uint16_t radius, float velocityX, float velocityY);
    uint16_t getX();
    uint16_t getY();
    void setX(uint16_t x);
    void setY(uint16_t y);
    float getVelocityX();
    float getVelocityY();
    void setVelocityX(float vx);
    void setVelocityY(float vy);
    uint16_t getBallRadius();
    SDL_Color *getColor();
    void render(SDL_Renderer *renderer);
};