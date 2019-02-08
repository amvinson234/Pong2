#ifndef OPTIONSMENU_H_INCLUDED
#define OPTIONSMENU_H_INCLUDED

#include "Menu.h"


class OptionsMenu : public Menu
{
public:
    OptionsMenu();
    ~OptionsMenu();
    sf::Font font;
    std::string Response(sf::RenderWindow & window);
};
#endif // OPTIONSMENU_H_INCLUDED
