#include <SFML/Graphics.hpp>
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "VisibleGameObject.h"
#include "PlayerPaddle.h"
#include "GameBall.h"
#include "GameObjectManager.h"
#include "ScoreBoard.h"
#include <iostream>

void Game::Start(void)
{
    if(_gameState != Uninitialized) return;
    _mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,64),"Pong - The Sequel!");

    _gameState = Game::ShowingSplash;

    sf::Clock clock;
    while(!IsExiting())
    {
        GameLoop(clock);
    }
    _mainWindow.close();
}

sf::RenderWindow& Game::GetWindow()
{
    return _mainWindow;
}

bool Game::IsExiting()
{
    if(_gameState == Game::Exiting) return true;
    else return false;
}

const GameObjectManager& Game::GetGameObjectManager()
{
    return _gameObjectManager;
}

void Game::GameLoop(sf::Clock& clock)
{
    sf::Event currentEvent;
    _mainWindow.pollEvent(currentEvent);
    float elapsedTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    switch(_gameState)
    {
    case Game::ShowingMenu:
        {
            ShowMenu();
            clock.restart();
            break;
        }
    case Game::ShowingSplash:
        {
            ShowSplashScreen();
            break;
        }
    case Game::Playing:
        {
            _mainWindow.clear(sf::Color(0,100,200));

            _scoreBoard->Draw(_mainWindow);
            _scoreBoard->Update(elapsedTime);

            _gameObjectManager.UpdateAll(elapsedTime);
            _gameObjectManager.DrawAll(_mainWindow);


            _mainWindow.display();

            if(currentEvent.type == sf::Event::Closed)
            {
                _gameState = Game::Exiting;
            }
            if(currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Escape)
            {
                _gameObjectManager.RemoveAll();
                _gameState = Game::ShowingMenu;
                _scoreBoard->~ScoreBoard();
            }
            if(currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::P)
            {
                std::cerr << " Paused ? " << std::endl;
                while(1)
                {
                    _mainWindow.pollEvent(currentEvent);
                    if(currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::P)
                    {
                        std::cerr << " end pause " << std::endl;
                        break;
                    }
                    clock.restart();
                }
            }

        }

    }

}

void Game::ShowSplashScreen()
{
    SplashScreen splashScreen;
    splashScreen.Show(_mainWindow);

    _gameState = Game::Playing;
    _gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
    switch(result)
    {
    case MainMenu::Exit:
        _gameState = Game::Exiting;
        break;
    case MainMenu::Play:
        PlayerPaddle *player1 = new PlayerPaddle();
        PlayerPaddle *player2 = new PlayerPaddle();

        player1->SetPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT - 70);
        player2->SetPosition(SCREEN_WIDTH/2, 70);

        GameBall *ball = new GameBall();
        ball->SetPosition(SCREEN_WIDTH/2, (SCREEN_HEIGHT / 2));

        _gameObjectManager.Add("Paddle1",player1);
        _gameObjectManager.Add("Paddle2",player2);
        _gameObjectManager.Add("Ball",ball);
        _gameState = Game::Playing;

        _scoreBoard = new ScoreBoard();

        break;
    }
}

ScoreBoard* Game::GetScoreBoard()
{
    return _scoreBoard;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
ScoreBoard *Game::_scoreBoard;
