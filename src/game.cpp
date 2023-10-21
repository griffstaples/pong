#include <iostream>
#include "SDL2/SDL.h"
#include "game.h"

PongGame::PongGame()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
    }
    else
    {
        window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        currentScreen = Home;

        if (window == NULL)
        {
            std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        }

        if (renderer == NULL)
        {
            std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        }
    }
}

void PongGame::runGame()
{
    while (!quitFlag)
    {

        // select which window
        if (currentScreen == Home)
        {
            // run screen
            HomeScreen homeScreen = HomeScreen(window, renderer, currentScreenP, quitFlagP);
            homeScreen.run();
        }
        else if (currentScreen == Play)
        {
            // run screen

            PlayScreen playScreen = PlayScreen(window, renderer, currentScreenP, quitFlagP);
            userWon = playScreen.run();
        }
        else if (currentScreen == Victory)
        {
            // run screen
            VictoryScreen victoryScreen = VictoryScreen(window, renderer, currentScreenP, quitFlagP, userWon);
            victoryScreen.run();
        }
    }

    // clean up window object when we close the window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

PongGame::~PongGame()
{
}
