

#include <iostream>
#include "SDL2/SDL.h"
#include "game.h"

int main()
{
    std::cout << "Starting program" << std::endl;

    PongGame game = PongGame();
    game.runGame();

    return 0;
}