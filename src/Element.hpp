#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <SFML/Graphics/Drwaable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Element : public sf::Drawable, public sf::Transformable
{
public:
    enum class Type
    {
        ROCK,
        PAPER,
        SCISSORS
    };

protected:
    Element(sf::Texture& texture, Type type, Type enemy);
    virtual ~Element();

    void switchType(const Type& type);
    Type getType() const;
    Type getEnemy() const;

private:
    static sf::IntRect getTextureRect(const Type& type);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Sprite  m_sprite;
    Type        m_type;
    Type        m_enemy;
}

#endif // ELEMENT_HPP