#include "GameObjectManager.h"
#include <map>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "VisibleGameObject.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
    std::for_each(_gameObjects.begin(),_gameObjects.end(),GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
    _gameObjects.insert(std::pair<std::string,VisibleGameObject*>(name,gameObject));
}

void GameObjectManager::Remove(std::string name)
{
    std::map<std::string,VisibleGameObject*>::iterator results = _gameObjects.find(name);
    if(results != _gameObjects.end())
    {
        delete results->second; //deletes pointer to game object
        _gameObjects.erase(results); //removes from list of game objects
    }
}

void GameObjectManager::RemoveAll()
{
    std::map<std::string,VisibleGameObject*>::iterator results;
    for(results = _gameObjects.begin(); results != _gameObjects.end(); results++)
    {
        Remove(results->first);
    }
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
    std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
    if(results == _gameObjects.end()) return NULL;
    return results->second;
}

int GameObjectManager::GetObjectCount() const
{
    return _gameObjects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow &window)
{
    std::map<std::string, VisibleGameObject*>::const_iterator results;
    for(results = _gameObjects.begin(); results != _gameObjects.end(); results++)
    {
        VisibleGameObject current_obj = *results->second;
        current_obj.Draw(window);
    }
}

void GameObjectManager::UpdateAll(float elapsedTime)
{
    std::map<std::string,VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
    while(itr != _gameObjects.end())
    {
        itr->second->Update(elapsedTime);
        itr++;
    }
}
