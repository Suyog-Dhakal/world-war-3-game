
#include <iostream>
#include "Player.h"

Player::Player(sf::Vector2f position, sf::Vector2f velocity, sf::Texture &playerTexture, int x) {
    sprite.setTexture(playerTexture);
    sprite.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
    sprite.setPosition(position.x, position.y);
    sprite.setScale(0.1,0.1);
    health = 100;
    id = x;
}

void Player::move(sf::Vector2f &moveByThis) {
    sf::Vector2f posVector = sprite.getPosition();
    if (posVector.x > 75 and posVector.x < 1225 and posVector.y > 100 and posVector.y < 600)
        sprite.move(moveByThis);
    else {
        if (posVector.x <= 75) {
            if (moveByThis.x < 0) moveByThis.x = 0;
        } else if (posVector.x >= 1225) {
            if (moveByThis. x > 0) moveByThis.x = 0;
        }

        if (posVector.y <= 100) {
            if (moveByThis.y < 0) moveByThis.y = 0;
        } else if (posVector.y >= 600) {
            if (moveByThis.y > 0) moveByThis.y = 0;
        }

        sprite.move(moveByThis);
    }
}

float Player::getSpeed() const {
    return speed;
}

void Player::setVelocity(float a, float b) {
    velocity.x = a;
    velocity.y = b;
}

void Player::rotatePlayer(sf::Vector2i rotation)
{
    if(rotation.x == 1)
        sprite.setRotation(0.0f);
    if(rotation.x == -1)
        sprite.setRotation(180.0f);
    if(rotation.y == 1)
        sprite.setRotation(270.0f);
    if(rotation.y == -1)
        sprite.setRotation(90.0f);
}


int Player::getId() {
    return id;
}

void Player::decreaseHealth() {
    health -= 10;
}

int Player::getHealth() {
    return health;
}

void Player::changeColor(sf::Color clr) {
    sprite.setColor(clr);
}

float Player::getRotation() {
    return sprite.getRotation();
}

void Player::setRotation(float angle) {
    sprite.setRotation(angle);
}

void Player::setHealth(int x) {
    health = x;
}
