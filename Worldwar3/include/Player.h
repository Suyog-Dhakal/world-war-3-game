
#ifndef CHAPTER_1_PLAYER_H
#define CHAPTER_1_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player: public Entity{
    //create a sprite, whose texture is obtained from class 'ResourceHolder'
    int health;
    float speed = 150;
    int id;

public:
    //implementation is pretty easy
    Player(sf::Vector2f position, sf::Vector2f velocity, sf::Texture &, int);

    void setVelocity(float a, float b);

    void move(sf::Vector2f &);

    void rotatePlayer(sf::Vector2i);
    float getRotation();
    void setRotation(float angle);
    void setHealth(int x);

    float getSpeed() const;

    int getId();

    void decreaseHealth();

    int getHealth();

    void changeColor(sf::Color);
};


#endif //CHAPTER_1_PLAYER_H
