#include <cstdint>
#include "paddle.h"

Paddle::Paddle(float x, float y, uint16_t width, uint16_t height, float velocityY)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->velocityY = velocityY;
};

float Paddle::getX()
{
    return x;
};

float Paddle::getY()
{
    return y;
};

void Paddle::setX(float x)
{
    this->x = x;
};

void Paddle::setY(float y)
{
    this->y = y;
};

float Paddle::getVelocityY()
{
    return velocityY;
};

void Paddle::setVelocityY(float velocityY)
{
    this->velocityY = velocityY;
}

uint16_t Paddle::getHeight()
{
    return height;
}

void Paddle::render(SDL_Renderer *renderer)
{
    uint16_t xInt, yInt;
    xInt = (uint16_t)x;
    yInt = (uint16_t)y;
    SDL_Rect rectFill = {xInt, yInt, width, height};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rectFill);
};
