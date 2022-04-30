#include "Brick.h"

Brick::Brick(float t_X, float t_Y, float t_Width, float t_Height)
{
    shape.setSize(sf::Vector2f(t_Width, t_Height));
    shape.setPosition(t_X, t_Y);
    shape.setOrigin(t_Width / 2.f, t_Height / 2.f);
    shape.setFillColor(sf::Color::Yellow);
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
}

float Brick::left()
{
    return this->shape.getPosition().x - shape.getSize().x / 2.f;
}

float Brick::right()
{
    return this->shape.getPosition().x + shape.getSize().x / 2.f;
}

float Brick::top()
{
    return this->shape.getPosition().y - shape.getSize().y / 2.f;
}

float Brick::bottom()
{
    return this->shape.getPosition().y + shape.getSize().y / 2.f;
}

sf::Vector2f Brick::getPosition()
{
    return shape.getPosition();
}

bool Brick::isDestroyed()
{
    return this->destroyed;
}

void Brick::destroy()
{
    this->destroyed = true;
}

sf::Vector2f Brick::getSize()
{
    return shape.getSize();
}

void Brick::update()
{

}
