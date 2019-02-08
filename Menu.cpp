#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

std::string Menu::Response(sf::RenderWindow & rw)
{
    return "";
}

void Menu::AddMenuItem(MenuItem item)
{
    _menuItems.push_back(item);
}

std::list<Menu::MenuItem>* Menu::GetMenuItems()
{
    return &_menuItems;
}


Menu::MenuItem Menu::HandleClick(int x, int y)
{
    std::list<MenuItem>::iterator it;

    for (it = _menuItems.begin(); it != _menuItems.end(); it++)
    {
        sf::Text menuItemText = it->itemBox;
        sf::FloatRect menuItemRect = menuItemText.getGlobalBounds();
        if(menuItemRect.top + menuItemRect.height > y && menuItemRect.top < y && menuItemRect.left < x && menuItemRect.left + menuItemRect.width > x) return (*it);
        menuItemRect = ((*it).valueBox).getGlobalBounds();
        if(menuItemRect.top + menuItemRect.height > y && menuItemRect.top < y && menuItemRect.left < x && menuItemRect.left + menuItemRect.width > x) return (*it);
        menuItemRect = (*it).optionBox1.getGlobalBounds();
        int max_dim = std::max(menuItemRect.height,menuItemRect.width);
        menuItemRect.width = max_dim;
        menuItemRect.height = max_dim;
        if(menuItemRect.top + menuItemRect.height > y && menuItemRect.top < y && menuItemRect.left < x && menuItemRect.left + menuItemRect.width > x) return (*it);
        menuItemRect = (*it).optionBox2.getGlobalBounds();
        max_dim = std::max(menuItemRect.height,menuItemRect.width);
        menuItemRect.height = max_dim;
        menuItemRect.width = max_dim;
        menuItemRect.top -= max_dim/2;
        if(menuItemRect.top + menuItemRect.height > y && menuItemRect.top < y && menuItemRect.left < x && menuItemRect.left + menuItemRect.width > x) return (*it);

    }
    MenuItem nothing;
    return nothing;
}
