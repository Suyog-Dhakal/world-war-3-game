//
// Created by udeshya on 2/21/20.
//

#ifndef WORLDWAR3_ENTITY_H
#define WORLDWAR3_ENTITY_H


#include <SFML/Graphics.hpp>

class Entity {
protected:
    sf::Vector2f velocity;
    sf::Sprite sprite;

    double toDegree(double rad);
public:
    sf::Sprite getSprite();
    sf::Vector2f getVelocity();
    sf::Vector2f getPosition();
    void move(sf::Vector2f);
    void draw(sf::RenderWindow&);
    void rotate(sf::Vector2f v);
    void setPosition(double x, double y);
};


#endif //WORLDWAR3_ENTITY_H
