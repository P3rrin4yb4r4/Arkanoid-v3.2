#ifndef BRICK_H
#define BRICK_H
#include <SFML/Graphics.hpp>

class Brick : public sf::Drawable
{
public:
    Brick(float t_X, float t_Y, float t_Width, float t_Height);
    Brick() = delete;
    ~Brick() = default;

    void update();
    sf::Vector2f getPosition();

    float left();
    float right();
    float top();
    float bottom();

    bool isDestroyed();
    void destroy();
    sf::Vector2f getSize();
private:
    sf::RectangleShape shape;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    bool destroyed{ false };
};

#endif // BRICK_H
