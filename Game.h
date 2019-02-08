#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "PlayerPaddle.h"
#include "GameObjectManager.h"
#include "ScoreBoard.h"

class Game
{

//static keyword: keeps all results in-scope throughout program lifetime
public:
    static void Start();
    static sf::RenderWindow& GetWindow();
    const static sf::Event GetInput();
    const static int SCREEN_WIDTH = 1024;
    const static int SCREEN_HEIGHT = 768;

    static GameObjectManager& GetGameObjectManager();

    static ScoreBoard* GetScoreBoard();

    static int _ballCount;


private:
    static bool IsExiting();
    static void GameLoop(sf::Clock & clock);

    static void ShowSplashScreen();
    static void ShowMenu();
    static void ShowOptions();
    enum GameState {Uninitialized, ShowingSplash, Paused, ShowingMenu, ShowingOptions, Playing, Exiting};

    static GameState _gameState;
    static sf::RenderWindow _mainWindow;
    static GameObjectManager _gameObjectManager;
    static ScoreBoard* _scoreBoard;
    static float _totalElapsedTime;
    static int _totalCount;
};


#endif // GAME_H_INCLUDED
