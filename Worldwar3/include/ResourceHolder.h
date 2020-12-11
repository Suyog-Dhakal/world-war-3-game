
#ifndef WORLDWAR3_RESOURCEHOLDER_H
#define WORLDWAR3_RESOURCEHOLDER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceHolder {
public:
    /*hold all 'sf::Textures' required for our game, this is done as to remove unnecessary burden of
    loading textures again and again, and also to keep our resources in one place, making it easy
    to access */
    sf::Texture backGround;
    sf::Texture player;
    sf::Texture bullet;
    sf::Texture menuBackground;

    sf::Texture explosion;

    sf::Font menuFont;
    sf::Font aboutFont;
    sf::Font gameOverFont;

    sf::SoundBuffer fireBuffer;


    ResourceHolder();
};


#endif //WORLDWAR3_RESOURCEHOLDER_H
