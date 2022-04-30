#include "Menu.h"

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("./Fonts/JOKERMAN.ttf"))
    {
        std::cout << "No font finded";
    }
    if (!menuMusic.openFromFile("./Sounds/MenuMusic.wav"))
    {
        std::cout << "No sound file founded!";
    }
    menuMusic.play();
    menuMusic.setLoop(true);

    title.setFont(font);
    title.setFillColor(sf::Color::Red);
    title.setCharacterSize(64);
    title.setString("Arkanoid");
    title.setPosition(sf::Vector2f(width / 3, height / 7));

    text[0].setFont(font);
    text[0].setFillColor(sf::Color::Red);
    text[0].setString("Play");
    text[0].setPosition(sf::Vector2f(width / 3, height / 2.0f));

    text[1].setFont(font);
    text[1].setFillColor(sf::Color::Red);
    text[1].setString("Options");
    text[1].setPosition(sf::Vector2f(width / 3, (height / 2.0f) + 50));

    text[2].setFont(font);
    text[2].setFillColor(sf::Color::Red);
    text[2].setString("Exit");
    text[2].setPosition(sf::Vector2f(width / 3, (height / 2.0f) + 100));

    selectedItemIndex = 0;
    text[selectedItemIndex].setFillColor(sf::Color::Blue);
}

Menu::~Menu()
{
    
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(title);
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(text[i]);
    }
}

void Menu::moveUp()
{
    if (selectedItemIndex >= 0)
    {
        text[selectedItemIndex].setFillColor(sf::Color::Red);

        selectedItemIndex--;
        if (selectedItemIndex < 0)
        {
            selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
        }
        text[selectedItemIndex].setFillColor(sf::Color::Blue);
        //std::cout << selectedItemIndex << std::endl;
    }
}

void Menu::moveDown()
{
    if (selectedItemIndex + 1 <= MAX_NUMBER_OF_ITEMS)
    {
        text[selectedItemIndex].setFillColor(sf::Color::Red);
        selectedItemIndex++;
        if (selectedItemIndex == MAX_NUMBER_OF_ITEMS)
        {
            selectedItemIndex = 0;
        }
        text[selectedItemIndex].setFillColor(sf::Color::Blue);
        //std::cout << selectedItemIndex << std::endl;
    }
}

void Menu::musicStop()
{
    menuMusic.stop();
}