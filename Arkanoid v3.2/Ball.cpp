#include "Ball.h"

Ball::Ball(float t_X, float t_Y)
{
    shape.setPosition(t_X, t_Y);
    shape.setRadius(this->ballRadius);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(this->ballRadius, this->ballRadius);
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
}

void Ball::update()
{
    shape.move(this->velocity);

    if (this->left() < 0) { velocity.x = ballVelocity; }
    else if (this->right() > SCREEN_X) { velocity.x = -ballVelocity; }
    else if (this->top() < 0) { velocity.y = ballVelocity; }
    else if (this->bottom() > SCREEN_Y) { velocity.y = -ballVelocity; }
}

float Ball::left()
{
    return this->shape.getPosition().x - this->shape.getRadius();
}

float Ball::right()
{
    return this->shape.getPosition().x + this->shape.getRadius();
}

float Ball::bottom()
{
    return this->shape.getPosition().y + this->shape.getRadius();
}

float Ball::top()
{
    return this->shape.getPosition().y - this->shape.getRadius();
}

void Ball::moveUp()
{
    this->velocity.y = -ballVelocity;
}

void Ball::moveDown()
{
    this->velocity.y = ballVelocity;
}

void Ball::moveLeft()
{
    this->velocity.x = -ballVelocity;
}

void Ball::moveRight()
{
    this->velocity.x = ballVelocity;
}

sf::Vector2f Ball::getPosition()
{
    return shape.getPosition();
}

void Ball::speedUp()
{
    this->ballVelocity++;
}

void Ball::ballStart()
{
    this->velocity.x = ballVelocity;
    this->velocity.y = ballVelocity;
}