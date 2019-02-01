#include "SplashScreen.h"
#include "Game.h"

void SplashScreen::Show(sf::RenderWindow& renderWindow)
{
    /*
    sf::Image image;
    if(image.loadFromFile("images/Splashscreen.png") != true)
    {
        return;
    }
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    */

    sf::Text title;
    sf::Text subtitle;
    sf::Font font;
    font.loadFromFile("FreeMonoBold.otf");
    title.setFont(font);
    subtitle.setFont(font);
    title.setString("PONG");
    subtitle.setString("\n\n The Sequel!");
    title.setCharacterSize(70);
    subtitle.setCharacterSize(45);
    title.setFillColor(sf::Color::Red);
    subtitle.setFillColor(sf::Color::Red);
    title.setStyle(sf::Text::Bold);
    subtitle.setStyle(sf::Text::Bold);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setPosition(512 - titleBounds.width/2-70,384 - titleBounds.height/2-70);
    subtitle.setPosition(512 - titleBounds.width/2-70,384 - titleBounds.height/2-70);

    //renderWindow.draw(sprite);
    renderWindow.clear(sf::Color::White);
    renderWindow.draw(title);
    renderWindow.draw(subtitle);
    renderWindow.display();

    sf::Event event;
    while(1)
    {
        while(renderWindow.pollEvent(event))
        {
            if(event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed)
            {
                return;
            }
        }
    }
}
