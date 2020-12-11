//
// Created by udeshya on 3/2/20.
//

#ifndef STAGE3_GLOBAL_H
#define STAGE3_GLOBAL_H
#include <SFML/System/Vector2.hpp>
#include "ResourceHolder.h"

struct receivedInfo{
    sf::Vector2f playerPosition;
    sf::Vector2f bulletEnd;
    float rotation;
    bool canOverRide = true;
};

#endif //STAGE3_GLOBAL_H
