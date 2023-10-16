#include "button.h"
#include "SDL2/SDL.h"

Button::Button(std::string text, uint8_t fontSize, uint8_t width, uint8_t height, uint8_t borderRadius, uint8_t paddingX, uint8_t paddingY)
{
    this->text = text;
    this->fontSize = fontSize;
    this->width = width;
    this->height = height;
    this->borderRadius = borderRadius;
    this->paddingX = paddingX;
    this->paddingY = paddingY;
};

Button::updateButton(std::string text, uint8_t fontSize, uint8_t width, uint8_t height, uint8_t borderRadius, uint8_t paddingX, uint8_t paddingY)
{
    this->text = text;
    this->fontSize = fontSize;
    this->width = width;
    this->height = height;
    this->borderRadius = borderRadius;
    this->paddingX = paddingX;
    this->paddingY = paddingY;
};

Button::render()
{
    SDL
}