#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <string>
#include <list>

class Menu
{
public:
Menu();
virtual ~Menu();
struct MenuItem
{
public:
    sf::Text itemBox; //this should always be filled. It's the Item listed in the menu. E.g. "Play" or "Exit" in main menu. Or "Ball Speed" in an options menu
    sf::Text valueBox; //optional. depicts current set value of the item in question. e.g. for item "Ball Speed", value might be displayed next to it, giving the currently set value.
    sf::Text optionBox1; //optional. there if we want to change the value of the item. e.g. plus sign to increase.
    sf::Text optionBox2;

    std::string result; //string which represents the menu item. e.g. "Play"
    int *value;
    std::string option1;
    std::string option2;
};

virtual std::string Response(sf::RenderWindow & rw); //rdraws all menu items. also returns string of selected menu item. (MenuItem.result)
virtual void AddMenuItem(MenuItem new_item);
virtual std::list<MenuItem>* GetMenuItems();
virtual MenuItem HandleClick(int x, int y);

private:
    std::list<MenuItem> _menuItems;
};


#endif // MENU_H_INCLUDED
