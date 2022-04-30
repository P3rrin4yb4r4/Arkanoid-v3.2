#include "Paddle.h"

Paddle::Paddle(float t_X, float t_Y)
{
    shape.setSize(this->paddleSize);
    shape.setPosition(t_X, t_Y);
    shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
    shape.setFillColor(sf::Color::White);
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
}

void Paddle::update()
{
    shape.move(this->velocity);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { velocity.x = paddleVelocity; }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { velocity.x = -paddleVelocity; }
    else { velocity.x = 0; }

    if (this->left() <= 0) { velocity.x = paddleVelocity; }
    else if (this->right() >= SCREEN_X) { velocity.x = -paddleVelocity; }
}

float Paddle::left()
{
    return this->shape.getPosition().x - shape.getSize().x / 2.f;
}

float Paddle::right()
{
    return this->shape.getPosition().x + shape.getSize().x / 2.f;
}

float Paddle::top()
{
    return this->shape.getPosition().y - shape.getSize().y / 2.f;
}

float Paddle::bottom()
{
    return this->shape.getPosition().y + shape.getSize().y / 2.f;
}

sf::Vector2f Paddle::getPosition()
{
    return shape.getPosition();
}
