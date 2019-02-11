#include "OptionsMenu.h"
#include "Game.h"
#include <iostream>
#include "Settings.h"

OptionsMenu::OptionsMenu()
{
    MenuItem initialSpeed;
    initialSpeed.itemBox.setString("Initial Ball Speed");
    initialSpeed.value = &GameSettings::initialSpeed;
    initialSpeed.valueBox.setString(std::to_string(GameSettings::initialSpeed));
    MenuItem maxBalls;
    maxBalls.value = &GameSettings::maxBalls;
    maxBalls.valueBox.setString(std::to_string(GameSettings::maxBalls));
    maxBalls.itemBox.setString("Max Number of Balls");
    MenuItem ballFreq;
    ballFreq.itemBox.setString("Frequency of New Balls");
    ballFreq.value = &GameSettings::ballFreq; //1 per 60 seconds
    ballFreq.valueBox.setString(std::to_string(GameSettings::ballFreq));
    MenuItem collSpeed;
    collSpeed.itemBox.setString("Speed Gained on Collision");
    collSpeed.value = &GameSettings::speedIncrement;
    collSpeed.valueBox.setString(std::to_string(GameSettings::speedIncrement));
    MenuItem maxScore;
    maxScore.itemBox.setString("Score to Win");
    maxScore.value = &GameSettings::maxScore;
    maxScore.valueBox.setString(std::to_string(GameSettings::maxScore));

    OptionsMenu::font.loadFromFile("FreeMonoBold.otf");

    MenuItem title;
    title.itemBox.setString("OPTIONS");
    title.itemBox.setFont(font);
    title.itemBox.setCharacterSize(60);
    title.itemBox.setFillColor(sf::Color(0,100,200));
    title.itemBox.setOrigin(title.itemBox.getLocalBounds().width / 2, title.itemBox.getLocalBounds().height/2);
    title.itemBox.setPosition(Game::SCREEN_WIDTH/2,120);

    MenuItem goBack;
    goBack.itemBox.setString("GO BACK");
    goBack.itemBox.setFont(font);
    goBack.itemBox.setCharacterSize(60);
    goBack.itemBox.setFillColor(sf::Color(0,100,200));
    goBack.itemBox.setOrigin(title.itemBox.getLocalBounds().width / 2, title.itemBox.getLocalBounds().height/2);
    goBack.itemBox.setPosition(Game::SCREEN_WIDTH/2,Game::SCREEN_HEIGHT - 120);

    AddMenuItem(title);
    AddMenuItem(goBack);
    AddMenuItem(initialSpeed);
    AddMenuItem(maxBalls);
    AddMenuItem(ballFreq);
    AddMenuItem(collSpeed);
    AddMenuItem(maxScore);

    std::list<MenuItem>* menuItems = GetMenuItems();
    int menu_size = menuItems->size();
    std::list<MenuItem>::iterator it;

    int ctr = 1;

    it = menuItems->begin();
    it++; it++;
    for(it; it != menuItems->end(); it++)
    {

        it->optionBox1.setString("+");
        it->optionBox2.setString("-");
        it->itemBox.setFont(font);
        it->valueBox.setFont(font);
        it->optionBox1.setFont(font);
        it->optionBox2.setFont(font);
        it->itemBox.setCharacterSize(int(Game::SCREEN_WIDTH / 1.75 / 30));
        it->valueBox.setCharacterSize(int(Game::SCREEN_WIDTH / 1.75 / 30));
        it->optionBox1.setCharacterSize(int(Game::SCREEN_WIDTH / 30 * 1.25));
        it->optionBox2.setCharacterSize(int(Game::SCREEN_WIDTH / 30 * 1.25));

        it->itemBox.setFillColor(sf::Color(0,100,200));
        it->valueBox.setFillColor(sf::Color(0,100,200));
        it->optionBox1.setFillColor(sf::Color(0,100,200));
        it->optionBox2.setFillColor(sf::Color(0,100,200));

        it->itemBox.setOrigin(it->itemBox.getLocalBounds().left, it->itemBox.getLocalBounds().top + it->itemBox.getLocalBounds().height / 2.);
        it->valueBox.setOrigin(it->valueBox.getLocalBounds().left, it->valueBox.getLocalBounds().top + it->valueBox.getLocalBounds().height / 2.);
        it->optionBox1.setOrigin(it->optionBox1.getLocalBounds().left, it->optionBox1.getLocalBounds().top + it->optionBox1.getLocalBounds().height / 2.);
        it->optionBox2.setOrigin(it->optionBox2.getLocalBounds().left, it->optionBox2.getLocalBounds().top + it->optionBox2.getLocalBounds().height / 2.);



        it->itemBox.setPosition(Game::SCREEN_WIDTH/10,Game::SCREEN_HEIGHT - Game::SCREEN_HEIGHT / menu_size - Game::SCREEN_HEIGHT / (menu_size+2) * ctr);
        it->valueBox.setPosition(Game::SCREEN_WIDTH/2,Game::SCREEN_HEIGHT - Game::SCREEN_HEIGHT / menu_size - Game::SCREEN_HEIGHT / (menu_size+2) * ctr);
        it->optionBox1.setPosition(Game::SCREEN_WIDTH*3.5/5,Game::SCREEN_HEIGHT - Game::SCREEN_HEIGHT / menu_size - Game::SCREEN_HEIGHT / (menu_size+2) * ctr);
        it->optionBox2.setPosition(Game::SCREEN_WIDTH*3.5/5 + 50,Game::SCREEN_HEIGHT - Game::SCREEN_HEIGHT / menu_size - Game::SCREEN_HEIGHT / (menu_size+2) * ctr);

        ctr++;
    }
}

OptionsMenu::~OptionsMenu()
{
}

std::string OptionsMenu::Response(sf::RenderWindow & rw)
{
    std::list<MenuItem>::iterator it;
    std::list<MenuItem> *menuItems = GetMenuItems();
//    std::string getString = menuItems->begin()->itemBox.getString();


    sf::Event event;
    MenuItem response;
    while(rw.pollEvent(event))
    {
        rw.clear(sf::Color::White);
        if(event.type == sf::Event::MouseButtonReleased)
        {
            response = HandleClick(event.mouseButton.x, event.mouseButton.y);
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            return "GO BACK";
        if(event.type == sf::Event::Closed)
            return "CLOSE";
        for(it = menuItems->begin(); it != menuItems->end(); it++)
        {
            if (response.itemBox.getString() == it->itemBox.getString() && it->itemBox.getString() == "GO BACK")
            {
                return "GO BACK";
            }
            sf::Text text;
            if (response.itemBox.getString() == it->itemBox.getString() && it->optionBox1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            {
                if((response.itemBox.getString() == "Initial Ball Speed" || response.itemBox.getString() == "Frequency of New Balls") && *(it->value) >= 10) *(it->value) += 5;
                else *(it->value) += 1;
                it->valueBox.setString(std::to_string(*(it->value)));
            }
            sf::FloatRect option2rect(it->optionBox2.getGlobalBounds().left,it->optionBox2.getGlobalBounds().top - it->optionBox2.getGlobalBounds().width / 2 ,it->optionBox2.getGlobalBounds().width,it->optionBox2.getGlobalBounds().width);
            if (response.itemBox.getString() == it->itemBox.getString() && option2rect.contains(event.mouseButton.x, event.mouseButton.y))
            {
                if((response.itemBox.getString() == "Initial Ball Speed" || response.itemBox.getString() == "Frequency of New Balls") && *(it->value) > 10) *(it->value) -= 5;
                else if(*(it->value) > 1) *(it->value) -= 1;
                it->valueBox.setString(std::to_string(*(it->value)));
            }
            rw.draw(it->itemBox);
            rw.draw(it->valueBox);
            rw.draw(it->optionBox1);
            rw.draw(it->optionBox2);
        }
        rw.display();
    }
    return "";
}
