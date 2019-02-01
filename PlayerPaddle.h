#ifndef PLAYERPADDLE_H_INCLUDED
#define PLAYERPADDLE_H_INCLUDED

#include "VisibleGameObject.h"

class PlayerPaddle :
    public VisibleGameObject //inheriting base class VisibleGameObject. Note that "public" keyword here means we're only inheriting the public functions! This helps hides complexity.
{
    public:
        PlayerPaddle();
        ~PlayerPaddle();

        void Update(float elapsedTime);
        void Draw(sf::RenderWindow& rw);

        float GetVelocity() const;

    private:
        float _velocity; // -- left ++ right
        float _maxVelocity;
};


#endif // PLAYERPADDLE_H_INCLUDED
