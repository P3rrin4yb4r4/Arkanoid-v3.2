#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#define SCREEN_Y 768
#define SCREEN_X 1024

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
private:
    const float ballRadius = 10.0f;
    sf::CircleShape shape;
    float ballVelocity = 6.0f;
    sf::Vector2f velocity{ 0, 0 };
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

#endif // BALL_H
