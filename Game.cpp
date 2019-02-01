#include <SFML/Graphics.hpp>
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "VisibleGameObject.h"
#include "PlayerPaddle.h"
#include "GameBall.h"
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
            break;
        }
    case Game::ShowingSplash:
        {
            ShowSplashScreen();
            break;
        }
    case Game::Playing:
        {
            _mainWindow.clear(sf::Color(255,0,0));
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
        player1->SetPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT - 70);

        GameBall *ball = new GameBall();
        ball->SetPosition(SCREEN_WIDTH/2, (SCREEN_HEIGHT / 2));

        _gameObjectManager.Add("Paddle1",player1);
        _gameObjectManager.Add("Ball",ball);
        _gameState = Game::Playing;
        break;
    }
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
