////////////////////////////////////////////////
#include "Element.hpp"

////////////////////////////////////////////////
Element::Element(sf::Texture& texture, Type type)
{
    // Set the sprite texture
    m_sprite.setTexture(texture);

    switchType(type);
}

////////////////////////////////////////////////
Element::~Element()
{

}

////////////////////////////////////////////////
sf::FloatRect Element::getGlobalBounds() const
{
    return {getPosition(), { m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height }};
}

////////////////////////////////////////////////
float Element::distance(const Element& element) const
{
    return std::sqrt(std::pow(getPosition().x - element.getPosition().x, 2) + std::pow(getPosition().y - element.getPosition().y, 2));
}

////////////////////////////////////////////////
Element::Type Element::getType() const
{
    return m_type;
}

////////////////////////////////////////////////
Element::Type Element::getEnemy() const
{
    switch(m_type)
    {
    case Type::ROCK:
        return Type::SCISSORS;
    case Type::PAPER:
        return Type::ROCK;
    case Type::SCISSORS:
        return Type::PAPER;
    default:
        return Type::ROCK;
    }
}

////////////////////////////////////////////////
const sf::Sprite& Element::getSprite() const
{
    return m_sprite;
}

////////////////////////////////////////////////
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

////////////////////////////////////////////////
void Element::switchType(const Type& type)
{
    m_type = type;

    // Set the sprite texture rect
    m_sprite.setTextureRect(getTextureRect(type));

    // Scale the sprite
    m_sprite.setScale(1, 1);
    m_sprite.setScale(WIDTH / m_sprite.getLocalBounds().width, HEIGHT / m_sprite.getLocalBounds().height);
}

////////////////////////////////////////////////
void Element::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
} 