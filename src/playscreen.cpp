

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "screen.h"
#include "playscreen.h"
#include <filesystem>
#include <iostream>

PlayScreen::PlayScreen(SDL_Window *window, SDL_Renderer *renderer, ScreenName *currentScreen, bool *quitFlag) : Screen(window, renderer, currentScreen, quitFlag)
{
    // Get window Size
    int windowX, windowY;
    SDL_GetWindowSize(window, &windowX, &windowY);

    // Create container for score
    int containerX, containerY, containerWidth, containerHeight;
    containerWidth = 200;
    containerHeight = 100;
    containerX = (windowX - containerWidth) / 2;
    containerY = (windowY - containerHeight) / 2;
    scoreRectangle = new SDL_Rect();
    *scoreRectangle = {containerX,
                       containerY,
                       containerWidth,
                       containerHeight};

    // Load font for score
    if (TTF_Init() == -1)
    {
        std::cout << "Error initializing TTF " << std::endl;
    }

    std::string currentDir = std::__fs::filesystem::current_path();
    std::string fontDir = currentDir + "/resources/Aldrich-Regular.ttf";
    font = TTF_OpenFont(fontDir.c_str(), 28);

    // initialize paddles
    userPaddle = new Paddle(0, (windowY - 40) / 2, 20, 40, 0);
    computerPaddle = new Paddle(windowX - 20, (windowY - 40) / 2, 20, 40, 0);

    int ballRadius = 10;
    int startX = windowX / 2 - ballRadius;
    int startY = windowY / 2 - ballRadius;
    float velocityX = 2.5;
    float velocityY = 2.5;

    // initialize balls
    ball = new Ball(startX, startY, ballRadius, velocityX, velocityY);
};

PlayScreen::~PlayScreen()
{
    delete ball;
    delete userPaddle;
    delete computerPaddle;
}

void PlayScreen::renderScore()
{

    std::string displayString = std::to_string(userScore) + " | " + std::to_string(computerScore);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, displayString.c_str(), {200, 255, 200, 100});
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, scoreRectangle);
};

void PlayScreen::handleDownMovement()
{
    userPaddle->setVelocityY(2);
};

void PlayScreen::handleUpMovement()
{
    userPaddle->setVelocityY(-2);
};

void PlayScreen::handleNoMovement()
{
    userPaddle->setVelocityY(0);
};

bool PlayScreen::run()
{
    SDL_FlushEvents(0, 1000);
    bool userWon;
    while (*currentScreen == Play && !(*quitFlag))
    {
        handleEvents();
        userWon = updateState();
        renderScreen();
    }
    return userWon;
};

void PlayScreen::handleEvents()
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
            if (e.key.keysym.sym == SDLK_DOWN)
            {
                // set y velocity to be positive
                handleDownMovement();
            }
            else if (e.key.keysym.sym == SDLK_UP)
            {
                // set y velocity to be negative
                handleUpMovement();
            }
        }
        else
        {
            handleNoMovement();
        }
    }
};

bool PlayScreen::updateState()
{
    // run physics
    float dt = 3;
    int windowX, windowY;
    SDL_GetWindowSize(window, &windowX, &windowY);

    float ballX = ball->getX();
    float ballY = ball->getY();
    float ballRadius = ball->getBallRadius();
    float ballVX = ball->getVelocityX();
    float ballVY = ball->getVelocityY();

    float userPaddleX = userPaddle->getX();
    float userPaddleY = userPaddle->getY();
    uint16_t userPaddleHeight = userPaddle->getHeight();
    uint16_t userPaddleWidth = 20;
    float userPaddleVY = userPaddle->getVelocityY();

    float computerPaddleX = computerPaddle->getX();
    float computerPaddleY = computerPaddle->getY();
    uint16_t computerPaddleHeight = computerPaddle->getHeight();
    float computerPaddleVY = computerPaddle->getVelocityY();

    //////////////////////////////////////////////////////////
    // Move User paddle
    float newPaddleY;
    newPaddleY = (int32_t)userPaddleY + userPaddleVY * dt;

    if (newPaddleY < 0)
    {
        userPaddle->setY(0);
    }
    else if (userPaddleY + userPaddleHeight > windowY)
    {
        userPaddle->setY(windowY - userPaddleHeight);
    }
    else
    {
        userPaddle->setY(newPaddleY);
    }
    //////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////
    // Calculate necessary computer paddle velocity
    // if ball moving towards computer
    if (ballVX > 0)
    {
        // set velocity to intercept ball
        float timeUntilCollision = abs((computerPaddleX - (ballX + ballRadius)) / ballVX);
        float deltaY = timeUntilCollision * ballVY;
        float calculatedY, calculatedVy;
        if (deltaY < 0)
        {
            if (abs(deltaY) > ballY)
            {
                calculatedY = abs((int32_t)(deltaY + (float)ballY) % windowY);
            }
            else
            {
                calculatedY = deltaY + (float)ballY;
            }
        }
        else
        {
            if (abs(deltaY + (float)ballY + (float)ballRadius) > windowY)
            {
                calculatedY = windowY - (int32_t)(deltaY + (float)ballY + (float)ballRadius) % windowY;
            }
            else
            {
                calculatedY = deltaY + (float)ballY + (float)ballRadius;
            }
        }

        // avoid divide by zero
        if (timeUntilCollision > 0.5)
        {
            calculatedVy = (calculatedY - (float)computerPaddleY) / timeUntilCollision;
            computerPaddle->setVelocityY(calculatedVy);
        }
    }
    else
    {
        // set velocity when ball is moving away from paddle
        computerPaddle->setVelocityY(0);
    }
    //////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////
    // Move computer paddle
    computerPaddleVY = computerPaddle->getVelocityY();
    newPaddleY = (float)computerPaddleY + computerPaddleVY * dt;

    if (newPaddleY < 0)
    {
        computerPaddle->setY(0);
    }
    else if (newPaddleY + computerPaddleHeight > windowY)
    {
        computerPaddle->setY(windowY - computerPaddleHeight);
    }
    else
    {
        computerPaddle->setY(newPaddleY);
    }
    //////////////////////////////////////////////////////////

    // Check for collision between ball and wall
    int32_t newBallY, newBallX;
    newBallY = (int32_t)ballY + ballVY * dt;

    if (newBallY <= 0)
    {
        // ball has collided with top wall
        ball->setVelocityY(-ballVY);
        ball->setY(-newBallY);
    }
    else if (newBallY + (int32_t)ballRadius >= windowY)
    {
        // ball has collided with bottom wall
        ball->setVelocityY(-ballVY);
        ball->setY(windowY - (newBallY + (int32_t)ballRadius - windowY));
    }
    else
    {
        ball->setY(newBallY);
    }

    //////////////////////////////////////////////////////////

    newBallY = ball->getY();
    newBallX = (int32_t)ballX + ballVX * dt;

    // check if ball collides with paddle
    // if ball collides with paddle, reflect
    // if ball is past paddle, let go through

    if (ballX < userPaddleX + userPaddleWidth)
    {
        // if already is past user paddle, let continue
        if (newBallX < 0)
        {
            // if ball touches line, reset game
            ++computerScore;
            ball->setX(100);
            ball->setY(100);
            ball->setVelocityX(2.5);
            ball->setVelocityY(2.5);
        }
        else
        {
            ball->setX(newBallX);
        }
    }
    else if (newBallX < userPaddleX + userPaddleWidth)
    {
        // if just past user paddle, check for y collision
        if (newBallY + ballRadius > userPaddleY && newBallY < userPaddleY + userPaddleHeight)
        {
            // collided, then reflect
            ball->setX(userPaddleX + userPaddleWidth - newBallX + userPaddleX + userPaddleWidth);
            ball->setVelocityX(-ballVX);
            // set Y velocity;
        }
        else
        {
            // no collision, continue
            ball->setX(newBallX);
        }
    }
    else if (ballX + ballRadius > computerPaddleX)
    {
        // if already is past user paddle, let continue
        if (newBallX + ballRadius > windowX)
        {
            // if ball touches line, reset game
            ++userScore;
            ball->setX(100);
            ball->setY(100);
            ball->setVelocityX(2.5);
            ball->setVelocityY(2.5);
        }
        else
        {
            ball->setX(newBallX);
        }
    }
    else if (newBallX + ballRadius > computerPaddleX)
    {
        // if just past computer paddle, check for y collision
        if (newBallY + ballRadius > computerPaddleY && newBallY < computerPaddleY + computerPaddleHeight)
        {
            // collided, then reflect
            ball->setX(computerPaddleX - ballRadius - ((float)newBallX + ballRadius - computerPaddleX));
            ball->setVelocityX(-ballVX);
            // set Y velocity;
        }
        else
        {
            // no collision, continue
            ball->setX(newBallX);
        }
    }
    else
    {
        // no collision
        ball->setX(newBallX);
    }

    if (computerScore >= 5)
    {
        *currentScreen = Victory;
        return false;
    }
    else if (userScore >= 5)
    {
        *currentScreen = Victory;
        return true;
    }

    return false;
};

void PlayScreen::renderScreen()
{
    // render background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // render score on top of background
    renderScore();

    // render paddles
    userPaddle->render(renderer);
    computerPaddle->render(renderer);

    // render ball
    ball->render(renderer);

    SDL_RenderPresent(renderer);
};