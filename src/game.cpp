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
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        homeScreen = new HomeScreen(window, renderer);
        playScreen = new PlayScreen(window, renderer);

        if (window == NULL)
        {
            std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        }
        else
        {
            // SDL_UpdateWindowSurface(window);
        }

        if (renderer == NULL)
        {
            std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
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

            if (e.type == SDL_KEYDOWN)
            {

                if (currentScreen == Home)
                {
                    if (e.key.keysym.sym == SDLK_RETURN)
                    {

                        std::cout << "Going to Play Screen" << std::endl;
                        currentScreen = Play;
                        delete playScreen;
                        playScreen = new PlayScreen(window, renderer);
                    }
                }
                else if (currentScreen == Play)
                {
                    if (e.key.keysym.sym == SDLK_DOWN)
                    {
                        // handle down movement
                        playScreen->handleDownMovement();
                    }
                    else if (e.key.keysym.sym == SDLK_UP)
                    {
                        // handle up movement
                        playScreen->handleUpMovement();
                    }
                }
            }
            else
            {
                if (currentScreen == Play)
                {
                    playScreen->handleNoMovement();
                }
            }
        }

        // do main program shit here
        SDL_RenderClear(renderer);

        // select which window
        if (currentScreen == Home)
        {
            // run screen
            homeScreen->renderScreen();
        }
        else if (currentScreen == Play)
        {
            // run screen
            int status = playScreen->runPhysics();
            playScreen->renderScreen();

            if (status == 1)
            {
                currentScreen = Home;
            }
        }
        else if (currentScreen == Victory)
        {
            // run screen
            // VictorScreen->renderScreen();
        }

        // handle user interaction
        SDL_RenderPresent(renderer);
    }

    // clean up window object when we close the window
    SDL_DestroyRenderer(renderer);
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