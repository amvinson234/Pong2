#include "PlayerPaddle.h"
#include "Game.h"
#include <cassert>
#include <SFML/Graphics.hpp>
#include <iostream>

PlayerPaddle::PlayerPaddle() :
    _velocity(0),
    _maxVelocity(600.0f)
{
    Load("images/paddle.png");
    assert(IsLoaded()); //if not loaded, then terminate the program

    GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);
}

PlayerPaddle::~PlayerPaddle()
{
}

void PlayerPaddle::Draw(sf::RenderWindow & rw)
{
    VisibleGameObject::Draw(rw);
}

float PlayerPaddle::GetVelocity() const
{
    return _velocity;
}

void PlayerPaddle::Update(float elapsedTime)
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) _velocity -= 3.0f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) _velocity += 3.0f;
    }
    else
    {
        _velocity -= elapsedTime*5*_velocity; //subtract off 5*velocity per second
    }
   // _velocity = 0;

    if(_velocity > _maxVelocity) _velocity = _maxVelocity;
    if(_velocity < -_maxVelocity) _velocity = -_maxVelocity;
    //std::cerr << _velocity << std::endl;
    sf::Vector2f pos = GetPosition();


    if(pos.x < GetSprite().getLocalBounds().width/2 || pos.x > (Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width/2))
    {
        _velocity = -_velocity; //bounce
    }

    float x_move = _velocity * elapsedTime;
    GetSprite().move(x_move,0);
}
