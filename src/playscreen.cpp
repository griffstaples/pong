

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "screen.h"
#include "playscreen.h"
#include <filesystem>
#include <iostream>

PlayScreen::PlayScreen(SDL_Window *window, SDL_Renderer *renderer) : Screen(window, renderer)
{
    this->window = window;
    this->renderer = renderer;

    int windowX, windowY;
    SDL_GetWindowSize(window, &windowX, &windowY);
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
    float velocityX = 1.5;
    float velocityY = 1.5;

    // initialize balls
    ball = new Ball(startX, startY, ballRadius, velocityX, velocityY);
};

PlayScreen::~PlayScreen()
{
    delete ball;
    delete userPaddle;
    delete computerPaddle;
}

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
};

void PlayScreen::renderScore()
{

    std::string displayString = std::to_string(userScore) + " | " + std::to_string(computerScore);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, displayString.c_str(), {200, 255, 200, 100});
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, scoreRectangle);
};

int PlayScreen::runPhysics()
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
    uint16_t computerPaddleWidth = 20;
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
            if (computerScore >= 5)
            {
                return 1;
            }
            ball->setX(100);
            ball->setY(100);
            ball->setVelocityX(1.5);
            ball->setVelocityY(1.5);
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
            if (userScore >= 5)
            {
                return 1;
            }
            ball->setX(100);
            ball->setY(100);
            ball->setVelocityX(1.5);
            ball->setVelocityY(1.5);
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

    // if collision, calculate new ball position and velocity
    // if not, calculate new ball position

    // Check for collision between ball and paddle
    // if collision calculate new ball position and velocity
    // if not, calculate new ball position

    return 0;
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
