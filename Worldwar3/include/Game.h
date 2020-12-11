
#ifndef CHAPTER_1_GAME_H
#define CHAPTER_1_GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "ResourceHolder.h"
#include <vector>


class Game {
protected:
    //data members
    //this class stores all the required textures to make gameplay smooth
    ResourceHolder resources;

    sf::Time elapsed;

    sf::Clock shootTimer;

    sf::Clock computerClock;

    int x ;
    int y;

    float deltaTime = 0.0f;

    //main window of our game, this is where our game executes
   sf::RenderWindow &mainWindow;

    //our main player
    Player mainPlayer;

    //enemy player
    Player enemyPlayer;

    //fire sound
    sf::Sound fire;

    //our maximum possible frame rate
    const sf::Time timePerFrame = sf::seconds(1 / 30.0f);

    //sprite of background, i.e desert, we obtain the texture from resourceHolder class
    sf::Sprite backgroundSprite;

    //bombing animation sprite
//    sf::Sprite bombingAnimation;

    //vector to store bullets current on the screen
    std::vector<Bullet> player1Bullets;
    std::vector<Bullet> player2Bullets;

    //private functions--------------------see .cpp file for implementation details
    //get user inputs and process them
    void processEvents();

    //update the position, velocity, etc of moving components using the corresponding input obtained
    //from processEvents() function
    void update(sf::Time &);


    //clear window and render everything on to our screen
    void render();

    //on mouse click, this function makes a bullet, appends it onto the 'bullets' vector
    //and gives it a velocity
    void shootBullet(float x, float y, Player &);

    //handle CPU Player
    void handleComputer();

    //detect collision
    void detectCollision();

    //display text
    void displayText(sf::RenderWindow &);

    void displayGameOver(int, int);

public:
    //public functions

    //game constructor
    Game(sf::RenderWindow&);

    //main game runs here
    void run();

};


#endif //CHAPTER_1_GAME_H
