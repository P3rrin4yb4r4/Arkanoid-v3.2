#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics.hpp>
#define SCREEN_Y 768
#define SCREEN_X 1024

class Paddle : public sf::Drawable
{
public:
    Paddle(float t_X, float t_Y);
    Paddle() = delete;
    ~Paddle() = default;
    void update();
    float left();
    float right();
    float top();
    float bottom();
    sf::Vector2f getPosition();
private:
    sf::RectangleShape shape;
    float paddleWidth{ 70.0f };
    float paddleHeight{ 10.0f };
    sf::Vector2f paddleSize{ this->paddleWidth, this->paddleHeight };
    const float paddleVelocity{ 8.0f };
    sf::Vector2f velocity{ paddleVelocity, 0.0f };
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

#endif // PADDLE_H
