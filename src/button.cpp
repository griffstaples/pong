// #include "button.h"
// #include "SDL2/SDL.h"
// #include "SDL2_TTF/SDL_ttf.h"

// Button::Button(std::string text, uint8_t fontSize, uint8_t width, uint8_t height, uint8_t borderRadius, uint8_t paddingX, uint8_t paddingY)
// {
//     this->text = text;
//     this->fontSize = fontSize;
//     this->width = width;
//     this->height = height;
//     this->borderRadius = borderRadius;
//     this->paddingX = paddingX;
//     this->paddingY = paddingY;
// };

// void Button::updateButton(std::string text, uint8_t fontSize, uint8_t width, uint8_t height, uint8_t borderRadius, uint8_t paddingX, uint8_t paddingY)
// {
//     this->text = text;
//     this->fontSize = fontSize;
//     this->width = width;
//     this->height = height;
//     this->borderRadius = borderRadius;
//     this->paddingX = paddingX;
//     this->paddingY = paddingY;
// };

// void Button::render(SDL_Renderer *renderer)
// {
//     // Create rectangle and render it
//     SDL_Rect rect = {100, 100, 300, 100};         // x, y, width, height
//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Black color
//     SDL_RenderFillRect(renderer, &rect);

//     // Create Text for text
//     SDL_Color textColor = {255, 255, 255}; // White color
//     TTF_Font *font = TTF_OpenFont("path/to/your/font.ttf", fontSize);
//     SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Press Enter to Play", textColor);
//     SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//     SDL_FreeSurface(textSurface);

//     SDL_RenderCopy(renderer, textTexture, NULL, &rect);
// };