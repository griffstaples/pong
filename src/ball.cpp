
#include "ball.h"

Ball::Ball(uint16_t x, uint16_t y, uint16_t radius, float velocityX, float velocityY)
{
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->velocityX = velocityX;
    this->velocityY = velocityY;
};

uint16_t Ball::getX()
{
    return x;
};

uint16_t Ball::getY()
{
    return y;
};

void Ball::setX(uint16_t x)
{
    this->x = x;
};

void Ball::setY(uint16_t y)
{
    this->y = y;
};

float Ball::getVelocityX()
{
    return velocityX;
};

float Ball::getVelocityY()
{
    return velocityY;
};

void Ball::setVelocityX(float vx)
{
    this->velocityX = vx;
};

void Ball::setVelocityY(float vy)
{
    this->velocityY = vy;
};

SDL_Color *Ball::getColor()
{
    return &color;
};

uint16_t Ball::getBallRadius()
{
    return radius;
}

void Ball::render(SDL_Renderer *renderer)
{
    SDL_Rect fillRect = {x, y, radius, radius};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &fillRect);
}
