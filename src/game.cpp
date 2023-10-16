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
        window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 300, SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        }
        else
        {
            SDL_UpdateWindowSurface(window);
        }
    }
}

void PongGame::runGame()
{
    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // do main program shit here
        // select which window
        if (currentScreen == HomeScreen)
        {
            // run screen
            handleUserInteractions();
            handlePhysics();
            renderWindow();
        }
        else if (currentScreen == PlayScreen)
        {
            // run screen
        }
        else if (currentScreen == VictoryScreen)
        {
            // run screen
        }

        // handle user interaction
        SDL_UpdateWindowSurface(window);
    }

    // clean up window object when we close the window
    SDL_DestroyWindow(window);
}

void PongGame::handleUserInteractions()
{
    // read user keyboard input
    // set user velocity based on that
    //
}

void PongGame::handlePhysics(){};
void PongGame::renderWindow(){};