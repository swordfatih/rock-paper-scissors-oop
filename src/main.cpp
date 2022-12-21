////////////////////////////////////////////////
#include "Element.hpp"

////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////
#include <random>
#include <iostream>
#include <algorithm>
#include <vector>

////////////////////////////////////////////////
const unsigned int ELEMENT_COUNT = 100;
const unsigned int MAX_X = 960;
const unsigned int MAX_Y = 480;

////////////////////////////////////////////////
std::vector<Element> random_elements(sf::Texture& texture);

////////////////////////////////////////////////
int main()
{
    sf::RenderWindow window(sf::VideoMode(MAX_X, MAX_Y), "SFML works!");
    window.setFramerateLimit(60);

    sf::Texture texture;
    texture.loadFromFile("assets/rps.png");

    std::vector<Element> elements = random_elements(texture);

    sf::Clock movement;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        { 
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(movement.getElapsedTime().asSeconds() > 0.1f)
        {
            movement.restart();

            for(auto& element : elements)
            {
                if(element.getPosition().x < 0)
                    element.setPosition(0, element.getPosition().y);
                else if(element.getPosition().x > MAX_X - element.getGlobalBounds().width)
                    element.setPosition(MAX_X - element.getGlobalBounds().width, element.getPosition().y);

                if(element.getPosition().y < 0)
                    element.setPosition(element.getPosition().x, 0);
                else if(element.getPosition().y > MAX_Y - element.getGlobalBounds().height)
                    element.setPosition(element.getPosition().x, MAX_Y - element.getGlobalBounds().height);

                Element* closest_enemy = nullptr;
                for(auto& enemy : elements)
                {
                    if(enemy.getType() == element.getEnemy())
                    {
                        if(element.getGlobalBounds().intersects(enemy.getGlobalBounds()))
                        {
                            enemy.switchType(element.getType());
                        }
                        else if(closest_enemy == nullptr || element.distance(enemy) < element.distance(*closest_enemy))
                        {
                            closest_enemy = &enemy;
                        }
                    }
                }

                if(closest_enemy != nullptr)
                {
                    sf::Vector2f vector = closest_enemy->getPosition() - element.getPosition();

                    if(vector.x != 0)
                        vector.x /= std::abs(vector.x);

                    if(vector.y != 0) 
                        vector.y /= std::abs(vector.y);

                    element.move(vector.x, vector.y);
                    closest_enemy->move(vector.x, vector.y);
                }
            } 
        }

        window.clear(sf::Color::White);

        for(auto& element : elements)
        {
            window.draw(element);
        }

        window.display();
    } 

    return 0;
}

////////////////////////////////////////////////
std::vector<Element> random_elements(sf::Texture& texture)
{
    std::vector<Element> elements;

    std::random_device m_device;  
    std::mt19937 m_gen(m_device()); 
    std::uniform_int_distribution<> m_distrib_type(0, 2);
    std::uniform_int_distribution<> m_distrib_pos_x(0, MAX_X);
    std::uniform_int_distribution<> m_distrib_pos_y(0, MAX_Y);

    for(unsigned int i = 0; i < ELEMENT_COUNT; ++i)
    {
        int rand_type = m_distrib_type(m_gen);

        Element::Type type;

        switch(rand_type)
        {
            case 0:
                type = Element::Type::ROCK;
                break;
            case 1:
                type = Element::Type::PAPER;
                break;
            default:
                type = Element::Type::SCISSORS;
                break;
        }

        Element element(texture, type);
        element.setPosition({float(m_distrib_pos_x(m_gen)), float(m_distrib_pos_y(m_gen))});
        elements.push_back(element);
    }

    return elements;
}