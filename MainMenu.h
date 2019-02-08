#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED
#include "SFML/Graphics.hpp"
#include <list>

class MainMenu
{
public:
    enum MenuResult {Nothing, Exit, Options, Play};

    struct MenuItem
    {
    public:
        sf::FloatRect rect;
        MenuResult action;
    };

    MenuResult Show(sf::RenderWindow& window);

private:
    MenuResult GetMenuResponse(sf::RenderWindow& window);
    MenuResult HandleClick(int x, int y);
    std::list<MenuItem> _menuItems;
};


#endif // MAINMENU_H_INCLUDED
