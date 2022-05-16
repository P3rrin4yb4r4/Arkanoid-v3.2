#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "Menu.h"
#include <vector>

#define SCREEN_Y 768
#define SCREEN_X 1024

#include <iostream>
#include <stdlib.h>
#include <ctime>

sf::Sound sound;
sf::Sound sound1;
sf::SoundBuffer bufferHit;
sf::SoundBuffer bufferPaddle;

// Sprawdzenie czy dwa obiekty się przenikają
template <class T1, class T2>
bool isIntersecting(T1& obj_1, T2& obj_2)
{
    return obj_1.right() >= obj_2.left() && obj_1.left() <= obj_2.right()
        && obj_1.bottom() >= obj_2.top() && obj_1.top() <= obj_2.bottom();
}

//Sprawdzenie kolizji obiektów paletka-piłka
bool collisionTest(Paddle& paddle, Ball& ball)
{
    if (!isIntersecting(paddle, ball)) return false;
    bufferHit.loadFromFile("./Sounds/hit.wav");
    sound1.setBuffer(bufferHit);
    sound1.play();
    ball.moveUp();

    if (ball.getPosition().x < paddle.getPosition().x)
    {
        ball.moveLeft();
    }
    else if (ball.getPosition().x > paddle.getPosition().x)
    {
        ball.moveRight();
    }
}

//Sprawdzenie kolizji obiektów piłka-bloczek
bool collisionTest(Brick& block, Ball& ball)
{
    if (!isIntersecting(block, ball)) return false;
    bufferPaddle.loadFromFile("./Sounds/hit.wav");
    sound.setBuffer(bufferPaddle);
    sound.play();
    block.destroy();

    float overlapLeft{ ball.right() - block.left() };
    float overlapRight{ block.right() - ball.left() };

    float overlapTop{ ball.bottom() - block.top() };
    float overlapBottom{ block.bottom() - ball.top() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    if (abs(minOverlapX) < abs(minOverlapY))
    {
        ballFromLeft ? ball.moveLeft() : ball.moveRight();
    }
    else
    {
        ballFromTop ? ball.moveUp() : ball.moveDown();
    }
}
int main()
{
    // Stworzenie okna menu
    sf::RenderWindow menuWindow(sf::VideoMode(SCREEN_X, SCREEN_Y), "Arkanoid ver. 2.0 - menu");

    Menu menu(menuWindow.getSize().x, menuWindow.getSize().y);

    while (menuWindow.isOpen())
    {
        // Event okna menu
        sf::Event eventMenu;
        while (menuWindow.pollEvent(eventMenu))
        {
            if(menuWindow.isOpen()) {}
            if (eventMenu.type == sf::Event::Closed)
            {
                menuWindow.close();
            }
            if (eventMenu.type == sf::Event::KeyReleased)
            {
                if (eventMenu.key.code == sf::Keyboard::Up)
                {
                    menu.moveUp();
                }
                if (eventMenu.key.code == sf::Keyboard::Down)
                {
                    menu.moveDown();
                }
                if (eventMenu.key.code == sf::Keyboard::Return)
                {
                    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Arkanoid ver. 2.0");
                    sf::RenderWindow options(sf::VideoMode(SCREEN_X, SCREEN_Y), "Options");
                    sf::RenderWindow about(sf::VideoMode(SCREEN_X, SCREEN_Y), "About");

                    int x = menu.MainMenuPressed();

                    // Wybranie opcji gry
                    if (x == 0)
                    {
                        menuWindow.close();
                        menu.musicStop();
                        
                        window.setFramerateLimit(60);

                        // Stworzenie tła gry
                        sf::Image image[3];
                        image[0].loadFromFile("tlo1.jpg");
                        image[1].loadFromFile("tlo2.jpg");
                        image[2].loadFromFile("tlo3.jpg");

                        srand(time(NULL));
                        int randomBackground = rand() % 3;

                        sf::Texture texture;
                        texture.loadFromImage(image[randomBackground]);

                        sf::Sprite background;
                        background.setTexture(texture);
                        
                        // Stworzenie obiektów paletki, piłki i bloczków
                        Paddle paddle(512, 700);
                        Ball ball(512, 700-16);

                        unsigned int blocksX{ 13 }, blocksY{ 7 }, blockWidth{ 60 }, blockWeight{ 20 };
                        std::vector<Brick> blocks;

                        for (int i = 0; i < blocksY; i++)
                        {
                            for (int j = 0; j < blocksX; j++)
                            {
                                blocks.emplace_back((j + 1) * (blockWidth + 10), (i + 2) * (blockWeight + 5), blockWidth, blockWeight);
                            }
                        }

                        bool start = false;
                        // Pętla gry
                        while (window.isOpen())
                        {
                            options.close();
                            about.close();

                            // Event okna gry
                            sf::Event event;
                            while (window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                                    window.close();
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !start)
                                {
                                    ball.ballStart();
                                    start = true;
                                }
                                if (!ball.statusOfBall())
                                {
                                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
                                        ball.moveLeft();
                                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                                        ball.moveRight();
                                }
                            }
                            
                            // Rysowanie okna - obiektów
                            window.clear();
                            menu.draw(window);
                            window.draw(background);
                            window.draw(ball);
                            window.draw(paddle);
                            for (auto& block : blocks) { window.draw(block); }

                            //Update
                            ball.update();
                            paddle.update();

                            //Collision check
                            collisionTest(paddle, ball);
                            for (auto& block : blocks) if (collisionTest(block, ball))
                            {
                                block.destroy();
                                break;
                            }

                            //Bricks destroy
                            auto iterator = remove_if(begin(blocks), end(blocks), [](Brick& block) {return block.isDestroyed(); });
                            blocks.erase(iterator, end(blocks));

                            // Wyświetlenie
                            window.display();
                        }
                    }
                }
            }
            menuWindow.clear(sf::Color::Black);
            menu.draw(menuWindow);
            menuWindow.display();
        }
    }
    return EXIT_SUCCESS;
}