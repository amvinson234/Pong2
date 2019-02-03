#include "MainMenu.h"
#include "SFML/Graphics.hpp"
#include <list>

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
    //Load menu image from file
  //  sf::Image image;
//    image.LoadFromFile("images/mainmenu.png");
  //  sf::Sprite sprite(image);

    sf::Text play_text;
    sf::Text exit_text;
    sf::Font font;
    font.loadFromFile("FreeMonoBold.otf");
    play_text.setFont(font);
    exit_text.setFont(font);
    play_text.setString("PLAY");
    exit_text.setString("EXIT");
    play_text.setCharacterSize(60);
    exit_text.setCharacterSize(60);
    play_text.setFillColor(sf::Color(0,100,200));
    exit_text.setFillColor(sf::Color(0,100,200));
    sf::FloatRect playBounds = play_text.getLocalBounds();
    sf::FloatRect exitBounds = exit_text.getLocalBounds();

    play_text.setPosition(window.getSize().x / 2 - playBounds.width / 2 , window.getSize().y / 2 - 70);
    exit_text.setPosition(window.getSize().x / 2 - exitBounds.width / 2 , window.getSize().y / 2 + 70);

    playBounds = play_text.getGlobalBounds();
    exitBounds = exit_text.getGlobalBounds();

    MenuItem playButton;
    playButton.action = Play;
    playButton.rect = playBounds;
    MenuItem exitButton;
    exitButton.action = Exit;
    exitButton.rect = exitBounds;

    _menuItems.push_back(playButton);
    _menuItems.push_back(exitButton);

    window.clear(sf::Color::White);
    window.draw(play_text);
    window.draw(exit_text);
    window.display();

    return GetMenuResponse(window);

}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
    std::list<MenuItem>::iterator it;

    for (it = _menuItems.begin(); it != _menuItems.end(); it++)
    {
        sf::FloatRect menuItemRect = (*it).rect;
        if(menuItemRect.top + menuItemRect.height > y && menuItemRect.top < y && menuItemRect.left < x && menuItemRect.left + menuItemRect.width > x) return (*it).action;
    }

    return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
    sf::Event menuEvent;
    while(1)
    {
        while(window.pollEvent(menuEvent))
        {
            //menuEvent.type
            if( menuEvent.type == sf::Event::MouseButtonPressed )
                return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
            if(menuEvent.type == sf::Event::Closed)
                return Exit;
        }
    }
}



