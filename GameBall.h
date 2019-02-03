#ifndef GAMEBALL_H_INCLUDED
#define GAMEBALL_H_INCLUDED

#include "VisibleGameObject.h"

class GameBall : public VisibleGameObject
{
public:
    GameBall();
    virtual ~GameBall();
    void Update(float elapsedTime);

private:
    float _velocity;
    float _angle;
    float _elapsedTimeSinceStart;

    float LinearVelocityX(float angle);
    float LinearVelocityY(float angle);
};


#endif // GAMEBALL_H_INCLUDED
