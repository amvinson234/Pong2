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
    sf::Keyboard::Key key_right;
    sf::Keyboard::Key key_left;
    if (dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1")) == this)
    {
        key_right = sf::Keyboard::Right;
        key_left = sf::Keyboard::Left;
    }
    else if (dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle2")) == this)
    {
        key_right = sf::Keyboard::D;
        key_left = sf::Keyboard::A;
    }
    else assert(0);

    if(sf::Keyboard::isKeyPressed(key_left) || sf::Keyboard::isKeyPressed(key_right))
    {
        if(sf::Keyboard::isKeyPressed(key_left)) _velocity -= 3.0f;
        if(sf::Keyboard::isKeyPressed(key_right)) _velocity += 3.0f;
    }
    else
    {
        _velocity -= elapsedTime*5*_velocity; //subtract off 5*velocity per second
    }


    if(_velocity > _maxVelocity) _velocity = _maxVelocity;
    if(_velocity < -_maxVelocity) _velocity = -_maxVelocity;
    sf::Vector2f pos = GetPosition();


    if (pos.x < GetSprite().getLocalBounds().width/2)
    {
        if (_velocity < 0) _velocity *= -1;
    }

    else if (pos.x > (Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width/2))
    {
        if (_velocity > 0) _velocity *= -1;
    }

    float x_move = _velocity * elapsedTime;

    GetSprite().move(x_move,0);

}
