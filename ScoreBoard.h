#ifndef SCOREBOARD_H_INCLUDED
#define SCOREBOARD_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "VisibleGameObject.h"
#include <string>

class ScoreBoard
{
public:
    ScoreBoard();
    ~ScoreBoard();

    void Update(float timeElapsed);
    void Draw(sf::RenderWindow & rw);
    void UpdateScore1();
    void UpdateScore2();

private:
    int _score1;
    int _score2;
    float _totalTimeElapsed;
};

#endif // SCOREBOARD_H_INCLUDED
