#include "Ball.h"
#include "Paddle.h"

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
    if (ballStatus == false)
    {
        ballVelocity = 8.0f;
        shape.move(this->velocity);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { velocity.x = ballVelocity; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { velocity.x = -ballVelocity; }
        else { velocity.x = 0; }
        
        if (this->left() <= 35.0f) { velocity.x = ballVelocity; }
        else if (this->right() >= SCREEN_X-35.0f) { velocity.x = -ballVelocity; }
    }
    if (ballStatus == true)
    {
        ballVelocity = 6.0f;
        shape.move(this->velocity);

        if (this->left() < 0) { velocity.x = ballVelocity; }
        else if (this->right() > SCREEN_X) { velocity.x = -ballVelocity; }
        else if (this->top() < 0) { velocity.y = ballVelocity; }
        
    }
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
    this->velocity.y = -ballVelocity;
    this->ballStatus = true;
}

bool Ball::statusOfBall()
{
    return ballStatus;
}

void Ball::beforeStart()
{
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    ballStatus = false;
}

void Ball::setPosition(sf::Vector2f p)
{
    return shape.setPosition(p);
}