#ifndef SCOREBOARD_H_INCLUDED
#define SCOREBOARD_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "VisibleGameObject.h"
#include <string>
#include "Settings.h"

class ScoreBoard
{
public:
    ScoreBoard();
    ~ScoreBoard();

    void Update(float timeElapsed);
    void Draw(sf::RenderWindow & rw);
    void UpdateScore1();
    void UpdateScore2();
    int gameStatus();

    enum Status {Playing, EndGame};
    static Status _status;

private:
    int _score1;
    int _score2;
    float _totalTimeElapsed;
};

#endif // SCOREBOARD_H_INCLUDED
