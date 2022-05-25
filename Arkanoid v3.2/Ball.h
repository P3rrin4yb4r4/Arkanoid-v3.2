#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#define SCREEN_Y 768
#define SCREEN_X 1024

#include <iostream>

class Ball : public sf::Drawable
{
public:
    Ball(float t_X, float t_Y);
    Ball() = delete;
    ~Ball() = default;
    void update();
    float left();
    float right();
    float bottom();
    float top();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    sf::Vector2f getPosition();
    void speedUp();
    void ballStart();
    bool statusOfBall();
private:
    float startPosition_x = 512.0f;
    float startPosition_y = 684.0f;
    bool ballStatus = false;
    const float ballRadius = 10.0f;
    sf::CircleShape shape;
    float ballVelocity = 6.0f;
    sf::Vector2f velocity{ 0, 0 };
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

#endif // BALL_H
