#include "GameBall.h"
#include "Game.h"
#include "SFML/Graphics.hpp"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <iostream>
#include "ScoreBoard.h"

GameBall::GameBall() :
    _velocity(220.0f),
    _elapsedTimeSinceStart(0.0f)
{
    Load("images/ball.png");
    assert(IsLoaded());

    GetSprite().setOrigin(15,15);

    //set random angle between 0 and 360 degrees
    srand(time(NULL));
    _angle = rand() % 361;
}

GameBall::~GameBall()
{
}

void GameBall::Update(float elapsedTime)
{
    _elapsedTimeSinceStart += elapsedTime;
    //Delay game from starting until 3 seconds have passed
    if(_elapsedTimeSinceStart < 3.0f) return;

    float moveAmount = _velocity * elapsedTime;
    float moveByX = LinearVelocityX(_angle) * moveAmount;
    float moveByY = LinearVelocityY(_angle) * moveAmount;

    //angle 0 points up, 180 points down, 90 points left, 270 points right
    //collide with left side of screen
    if(GetPosition().x + moveByX <= 0 + GetWidth()/2
        || GetPosition().x + GetHeight()/2 + moveByX >= Game::SCREEN_WIDTH)
    {
        _angle = 360 - _angle;
        if(_angle > 260 && _angle < 280) _angle += 20; //So doesn't bounce back parallel to the paddles
        if(_angle > 80 && _angle < 100) _angle += 20;
        moveByX = -moveByX;
    }


    PlayerPaddle *player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
    PlayerPaddle *player2 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle2"));
    ScoreBoard *scoreBoard = dynamic_cast<ScoreBoard*>(Game::GetScoreBoard());


    if(player1 != NULL && player2 != NULL)
    {
        sf::FloatRect p1BB = player1->GetBoundingRect();
        sf::FloatRect p2BB = player2->GetBoundingRect();
        if(p1BB.intersects(GetBoundingRect()))
        {
            _angle = 360 - (_angle - 180);
            if(_angle > 360) _angle -= 360;

            moveByY *= -1;

            //make sure ball isn't inside paddle
            if(GetBoundingRect().top + GetBoundingRect().height > player1->GetBoundingRect().top)
            {
                SetPosition(GetPosition().x, player1->GetBoundingRect().top - GetWidth()/2 - 1);
            }

            float playerVelocity = player1->GetVelocity();

            if(playerVelocity < 10)
            {
                //moving left
                _angle -= 20; //give angle an extra kick leftward if paddle moving left
                if(_angle < 0) _angle = 360 - _angle;
            }
            else if (playerVelocity > 10)
            {
                //moving right
                _angle += 20; //give angle extra kick rightward if paddle moving right
                if(_angle > 360) _angle -= 360;
            }
            _velocity += 5.0f; //add to velocity after each hit of the paddle
        }


        if(p2BB.intersects(GetBoundingRect()))
        {
            _angle = 360 - (_angle - 180);
            if(_angle > 360) _angle -= 360;

            moveByY *= -1;

            //make sure ball isn't inside paddle
            if(GetBoundingRect().top < player2->GetBoundingRect().top + player2->GetBoundingRect().height)
            {
                SetPosition(GetPosition().x, player2->GetBoundingRect().top + player2->GetBoundingRect().height + GetWidth()/2 + 1);
            }

            float playerVelocity = player2->GetVelocity();

            if(playerVelocity < 10)
            {
                //moving left
                _angle += 20; //give angle an extra kick leftward if paddle moving left
                if(_angle < 0) _angle = 360 - _angle;
            }
            else if (playerVelocity > 10)
            {
                //moving right
                _angle -= 20; //give angle extra kick rightward if paddle moving right
                if(_angle > 360) _angle -= 360;
            }
            _velocity += 5.0f; //add to velocity after each hit of the paddle
        }

        if(GetPosition().y + GetHeight()/2 + moveByY >= Game::SCREEN_HEIGHT
         || GetPosition().y - GetHeight()/2 + moveByY < 0)
        {
            if(GetPosition().y - GetHeight()/2 + moveByY < 0) scoreBoard->UpdateScore1();
            if(GetPosition().y + GetHeight()/2 + moveByY >= Game::SCREEN_HEIGHT)  scoreBoard->UpdateScore2();
            //If fell below lower bounds
            //Move to middle of the screen for now and randomize angle
            GetSprite().setPosition(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);
            _angle = rand() % 361;
            _velocity = 220.0f;
            _elapsedTimeSinceStart = 0.0f;

        }


        GetSprite().move(moveByX,moveByY);
    }

}

float GameBall::LinearVelocityX(float angle)
{
    angle -= 90;

    if (angle < 0) angle = 360 + angle;
    return (float)std::cos(angle * (std::atan(1.0)*4 / 180.0f));
}

float GameBall::LinearVelocityY(float angle)
{
    angle -= 90;
    if (angle < 0) angle = 360 + angle;
    return (float)std::sin(angle * (std::atan(1.0)*4 / 180.0f));
}
