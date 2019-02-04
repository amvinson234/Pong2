#include "ScoreBoard.h"
#include <string>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include <iostream>

ScoreBoard::ScoreBoard()
{
    _score1 = 0;
    _score2 = 0;
    _totalTimeElapsed = 0;
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::Update(float elapsedTime)
{
    _totalTimeElapsed += elapsedTime;
}


void ScoreBoard::UpdateScore1()
{
    _score1++;
}

void ScoreBoard::UpdateScore2()
{
    _score2++;
}

void ScoreBoard::Draw(sf::RenderWindow & rw)
{
    sf::Text timer;
    sf::Text scorePlayer1;
    sf::Text scorePlayer2;

    sf::Font font;
    font.loadFromFile("FreeMonoBold.otf");
    timer.setFont(font);
    scorePlayer1.setFont(font);
    scorePlayer2.setFont(font);
    timer.setCharacterSize(20);
    scorePlayer1.setCharacterSize(20);
    scorePlayer2.setCharacterSize(20);
    timer.setColor(sf::Color::Black);
    scorePlayer1.setColor(sf::Color::Black);
    scorePlayer2.setColor(sf::Color::Black);

    scorePlayer1.setString("Player 1 Score: " + std::to_string(_score1));
    scorePlayer2.setString("Player 2 Score: " + std::to_string(_score2));

    std::string time_seconds = std::to_string(int(_totalTimeElapsed));
    timer.setString("Time Elapsed: " + time_seconds + " sec");

    scorePlayer1.setPosition(Game::SCREEN_WIDTH - scorePlayer1.getLocalBounds().width - 25, Game::SCREEN_HEIGHT - 150 - scorePlayer1.getLocalBounds().height);
    scorePlayer2.setPosition(Game::SCREEN_WIDTH - scorePlayer2.getLocalBounds().width - 25, 150);
    rw.draw(scorePlayer1);
    rw.draw(scorePlayer2);
    rw.draw(timer);
}
