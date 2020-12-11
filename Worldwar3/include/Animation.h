//
// Created by Sandesh on 1/23/2020.

#ifndef PRAC2_ANIMATION_H
#define PRAC2_ANIMATION_H

#include <SFML/Graphics.hpp>


class Animation {

public:
    Animation( sf::Texture* texture, sf::Vector2u imageCount, float switchTime );

    void Update(int row, float deltaTime );

public:
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage ;

    float totalTime;
    float  switchTime;
};


#endif //PRAC2_ANIMATION_H
