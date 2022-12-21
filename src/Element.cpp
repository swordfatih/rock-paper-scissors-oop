#include "Element.hpp"

Element::Element(sf::Texture& texture, Type type, Type enemy)
    : type(type)
    , enemy(enemy)
{
    // Set the sprite texture
    sprite.setTexture(texture);

    // Set the sprite texture rect
    sprite.setTextureRect(getTextureRect(type));
}

Element::~Element()
{

}

Element::Type Element::getType() const
{
    return type;
}

Element::Type Element::getEnemy() const
{
    return enemy;
}

sf::IntRect Element::getTextureRect(const Type& type)
{
    switch(type)
    {
    case Type::ROCK:
        return sf::IntRect(650, 350, 350, 230);
    case Type::PAPER:
        return sf::IntRect(400, 670, 420, 310);
    case Type::SCISSORS:
        return sf::IntRect(300, 140, 270, 450);
    default:
        return sf::IntRect(0, 0, 0, 0);
    }
}

void Element::switchType(const Type& type)
{
    this->type = type;
    sprite.setTextureRect(getTextureRect(type));

    switch(type)
    {
    case Type::ROCK:
        enemy = Type::PAPER;
        break;
    case Type::PAPER:
        enemy = Type::SCISSORS;
        break;
    case Type::SCISSORS:
        enemy = Type::ROCK;
        break;
    default:
        break;
    }
}

void Element::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}