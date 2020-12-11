
#include "Bullet.h"
#include <math.h>
#include <iostream>

//bullet constructor
Bullet::Bullet(sf::Vector2f pos, sf::Vector2f vel, sf::Texture &bulletTexture) {
    sprite.setPosition(pos);
    sprite.setScale(0.7, 0.7);
    velocity = vel;
    sprite.setTexture(bulletTexture);
}