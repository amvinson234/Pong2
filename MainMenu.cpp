#include "MainMenu.h"
#include "SFML/Graphics.hpp"
#include <list>

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
    sf::Text play_text;
    sf::Text exit_text;
    sf::Text options_text;
    sf::Font font;
    font.loadFromFile("FreeMonoBold.otf");
    play_text.setFont(font);
    options_text.setFont(font);
    exit_text.setFont(font);
    play_text.setString("PLAY");
    options_text.setString("OPTIONS");
    exit_text.setString("EXIT");
    play_text.setCharacterSize(60);
    options_text.setCharacterSize(60);
    exit_text.setCharacterSize(60);
    play_text.setFillColor(sf::Color(0,100,200));
    options_text.setFillColor(sf::Color(0,100,200));
    exit_text.setFillColor(sf::Color(0,100,200));
    sf::FloatRect playBounds = play_text.getLocalBounds();
    sf::FloatRect optionsBounds = options_text.getLocalBounds();
    sf::FloatRect exitBounds = exit_text.getLocalBounds();

    play_text.setOrigin(play_text.getLocalBounds().width / 2, play_text.getLocalBounds().height/2);
    options_text.setOrigin(options_text.getLocalBounds().width / 2, options_text.getLocalBounds().height/2);
    exit_text.setOrigin(exit_text.getLocalBounds().width / 2, exit_text.getLocalBounds().height / 2);
    play_text.setPosition(window.getSize().x / 2 , window.getSize().y / 2 - 140);
    options_text.setPosition(window.getSize().x / 2, window.getSize().y / 2 );
    exit_text.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 140);

    playBounds = play_text.getGlobalBounds();
    optionsBounds = options_text.getGlobalBounds();
    exitBounds = exit_text.getGlobalBounds();

    MenuItem playButton;
    playButton.action = Play;
    playButton.rect = playBounds;
    MenuItem optionsButton;
    optionsButton.action = Options;
    optionsButton.rect = optionsBounds;
    MenuItem exitButton;
    exitButton.action = Exit;
    exitButton.rect = exitBounds;

    _menuItems.push_back(playButton);
    _menuItems.push_back(optionsButton);
    _menuItems.push_back(exitButton);

    window.clear(sf::Color::White);
    window.draw(play_text);
    window.draw(options_text);
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
            if( menuEvent.type == sf::Event::MouseButtonPressed )
                return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
            if(menuEvent.type == sf::Event::Closed)
                return Exit;
        }
    }
}
