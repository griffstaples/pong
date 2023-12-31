#include <iostream>
#include "homescreen.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <filesystem>
#include <string>

HomeScreen::HomeScreen(SDL_Window *screenWindow, SDL_Renderer *screenRenderer, ScreenName *currentScreen, bool *quitFlag) : Screen(screenWindow, screenRenderer, currentScreen, quitFlag)
{

    // Get window size
    int windowX, windowY;
    SDL_GetWindowSize(window, &windowX, &windowY);

    // Configure button size
    int buttonWidth = 300; // px
    int buttonHeight = 80; // px
    int buttonTopLeftX = (windowX - buttonWidth) / 2;
    int buttonTopLeftY = (windowY - buttonHeight) / 2;
    button = {buttonTopLeftX, buttonTopLeftY, buttonWidth, buttonHeight};

    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        std::cerr << "Error occurred initializing SDL_ttf" << std::endl;
    }

    // Create button text
    SDL_Color textColor = {0, 0, 0, 255}; // black color
    std::string workspaceDir = std::__fs::filesystem::current_path();
    std::string fontDir = workspaceDir + "/resources/Aldrich-Regular.ttf";
    TTF_Font *font = TTF_OpenFont(fontDir.c_str(), 28);

    if (font == NULL)
    {
        std::cout << "Font not found" << std::endl;
    }
    else
    {

        SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Press Enter to Play", textColor);

        if (textSurface == NULL)
        {
            std::cout << "Failed to create text surface: " << TTF_GetError() << std::endl;
        }
        else
        {
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            if (textTexture == NULL)
            {
                std::cout << "Failed to create text texture: " << TTF_GetError() << std::endl;
            }

            SDL_FreeSurface(textSurface);
        }

        TTF_CloseFont(font); // Close the font when done.
    }
};

void HomeScreen::run()
{
    while (*currentScreen == Home && !(*quitFlag))
    {
        handleEvents();
        updateState();
        renderScreen();
    }
};

void HomeScreen::handleEvents()
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            *quitFlag = true;
            return; // exit loop
        }

        if (e.type == SDL_KEYDOWN)
        {

            if (e.key.keysym.sym == SDLK_RETURN)
            {
                std::cout << "Going to Play Screen" << std::endl;
                *currentScreen = Play;
                break;
            }
        }
    }
};

void HomeScreen::updateState(){
    // add animation here possibly
};

void HomeScreen::renderScreen()
{

    // Render background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer); // this sets all pixels to the draw colour;

    // Render button background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white color
    SDL_RenderFillRect(renderer, &button);

    // Create Text for text
    SDL_RenderCopy(renderer, textTexture, NULL, &button);
    SDL_RenderPresent(renderer);
};

HomeScreen::~HomeScreen()
{
    SDL_DestroyTexture(textTexture);
}