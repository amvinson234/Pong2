#ifndef GAMEOBJECTMANAGER_H_INCLUDED
#define GAMEOBJECTMANAGER_H_INCLUDED
#include "VisibleGameObject.h"
#include "SFML/Graphics.hpp"
#include <map>

class GameObjectManager
{
public:
    GameObjectManager();
    ~GameObjectManager();

    void Add(std::string name, VisibleGameObject* gameObject);
    void Remove(std::string name);
    int GetObjectCount() const; //const after function declaration prevents function from altering any member variables of the class?
    VisibleGameObject* Get(std::string name) const;

    void RemoveAll();
    void DrawAll(sf::RenderWindow& renderWindow);
    void UpdateAll(float elapsedTime);

private:
    std::map<std::string, VisibleGameObject*> _gameObjects; //note that we're pointing to VisibleGameObject because we want the object that is pointed to to last beyond the scope of where it's created

    struct GameObjectDeallocator
    {
        void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
        {
            delete p.second;
        }
    };
};


#endif // GAMEOBJECTMANAGER_H_INCLUDED
