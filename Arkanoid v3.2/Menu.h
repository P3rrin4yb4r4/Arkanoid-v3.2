#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
    Menu(float width, float height);
    Menu() = delete;
    ~Menu();

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();

    int MainMenuPressed()
    {
        return selectedItemIndex;
    }

    void musicStop();
private:
    int selectedItemIndex;
    sf::Music menuMusic;
    sf::Font font;
    sf::Text title;
    sf::Text text[MAX_NUMBER_OF_ITEMS];
};

#endif // MENU_H
