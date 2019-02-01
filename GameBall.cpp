#include "GameBall.h"
#include <cassert>

GameBall::GameBall()
{
    Load("images/ball.png");
    assert(IsLoaded());

    GetSprite().setOrigin(15,15);
}

GameBall::~GameBall()
{
}
