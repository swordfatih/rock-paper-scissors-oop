#ifndef ELEMENT_HPP
#define ELEMENT_HPP

////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <cmath>

////////////////////////////////////////////////
const unsigned int WIDTH = 40;
const unsigned int HEIGHT = 40;

////////////////////////////////////////////////
class Element : public sf::Drawable, public sf::Transformable
{
public:
    enum class Type
    {
        ROCK,
        PAPER,
        SCISSORS
    };

    Element(sf::Texture& texture, Type type);
    virtual ~Element();

    sf::FloatRect getGlobalBounds() const;
    float distance(const Element& element) const;
    void switchType(const Type& type);
    Type getType() const;
    Type getEnemy() const;
    const sf::Sprite& getSprite() const;

private:
    static sf::IntRect getTextureRect(const Type& type);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Sprite  m_sprite;
    Type        m_type;
};

#endif // ELEMENT_HPP