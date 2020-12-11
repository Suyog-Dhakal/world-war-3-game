//
// Created by udeshya on 2/21/20.
//

#include "Entity.h"
#include <cmath>

sf::Sprite Entity::getSprite() {
    return sprite;
}

sf::Vector2f Entity::getVelocity() {
    return velocity;
}

sf::Vector2f Entity::getPosition() {
    return (sprite.getPosition());
}

void Entity::move(sf::Vector2f v){
    sprite.move(v);
}

void Entity::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

double Entity::toDegree(double rad) {
    return ((180/M_PI) * rad);
}

void Entity::rotate(sf::Vector2f v) {
    if ((v.x > 0 and v.y > 0) or (v.x > 0 and v.y < 0))
        sprite.setRotation(toDegree(atan(v.y / v.x)));
    else if ((v.x < 0 and v.y > 0) or (v.x < 0 and v.y < 0))
        sprite.setRotation(180 + toDegree(atan(v.y / v.x)));
}

void Entity::setPosition(double x, double y) {
    sprite.setPosition(x,y);
}
