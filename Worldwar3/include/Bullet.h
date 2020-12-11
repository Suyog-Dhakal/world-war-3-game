
#ifndef WORLDWAR3_BULLET_H
#define WORLDWAR3_BULLET_H


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Bullet: public Entity{
    //sprite and velocity are inherited from entity
public:
    //constructor
    Bullet(sf::Vector2f pos, sf::Vector2f vel, sf::Texture &);

};


#endif //WORLDWAR3_BULLET_H
