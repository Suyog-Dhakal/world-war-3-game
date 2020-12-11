//
// Created by udeshya on 3/1/20.
//

#include <SFML/Network/Packet.hpp>
#include <Client.h>
#include <Server.h>
#include <iostream>
#include "MultiPlayerGame.h"
#include "Global.h"

/*Testing part*/
#define port1 9900
#define port2 10000

MultiPlayerGame::MultiPlayerGame(sf::RenderWindow &pWindow, const std::string& ip, bool isMain) : Game(pWindow),
    server(isMain?port1:port2), client(ip, isMain?port2:port1, isMain)
{
    isMainPlayer = isMain;
}
/*END OF TESTING PART*/

void MultiPlayerGame::run() {
    sf::Clock clock;
    sf::Clock gameTick;
    sf::Time delay = sf::Time::Zero;

    while (mainWindow.isOpen()) {
        if (mainPlayer.getHealth() > 0 and enemyPlayer.getHealth() > 0) {
            processEvents();
            delay += clock.restart();
            while (delay.asSeconds() > timePerFrame.asSeconds()) {
                delay -= timePerFrame;
                if (gameTick.getElapsedTime().asSeconds() > 2) {
                    handleComputer();
                    gameTick.restart();
                }
                processEvents();
                update(const_cast<sf::Time &>(timePerFrame));
            }
        } else if (mainPlayer.getHealth() == 0 or enemyPlayer.getHealth() == 0)
        {
            
            displayGameOver(mainPlayer.getHealth(), enemyPlayer.getHealth());
            break;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            break;
        render();
    }
}
void MultiPlayerGame::handleComputer() {
    //null body, because we don't need to handle computer
}


void MultiPlayerGame::update(sf::Time &delay) {
    elapsed = shootTimer.getElapsedTime();
    //record events for main player only
    bool dataSent;

    if (isMainPlayer) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            mainPlayer.rotatePlayer(sf::Vector2i(0, 1));
            mainPlayer.setVelocity(mainPlayer.getVelocity().x, -mainPlayer.getSpeed());
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            mainPlayer.rotatePlayer(sf::Vector2i(0, -1));
            mainPlayer.setVelocity(mainPlayer.getVelocity().x, mainPlayer.getSpeed());
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            mainPlayer.rotatePlayer(sf::Vector2i(-1, 0));
            mainPlayer.setVelocity(-mainPlayer.getSpeed(), mainPlayer.getVelocity().y);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            mainPlayer.rotatePlayer(sf::Vector2i(1, 0));
            mainPlayer.setVelocity(mainPlayer.getSpeed(), mainPlayer.getVelocity().y);
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && elapsed.asSeconds() > 1) {
            shootBullet(sf::Mouse::getPosition(mainWindow).x, sf::Mouse::getPosition(mainWindow).y, mainPlayer);
            dataSent = true;
            shootTimer.restart();
        } else {
            mainPlayer.setVelocity(0, 0);
        }
    }
    else{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            enemyPlayer.rotatePlayer(sf::Vector2i(0, 1));
            enemyPlayer.setVelocity(enemyPlayer.getVelocity().x, -enemyPlayer.getSpeed());
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            enemyPlayer.rotatePlayer(sf::Vector2i(0, -1));
            enemyPlayer.setVelocity(enemyPlayer.getVelocity().x, enemyPlayer.getSpeed());
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            enemyPlayer.rotatePlayer(sf::Vector2i(-1, 0));
            enemyPlayer.setVelocity(-enemyPlayer.getSpeed(), enemyPlayer.getVelocity().y);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            enemyPlayer.rotatePlayer(sf::Vector2i(1, 0));
            enemyPlayer.setVelocity(enemyPlayer.getSpeed(), enemyPlayer.getVelocity().y);
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && elapsed.asSeconds() > 1) {
            shootBullet(sf::Mouse::getPosition(mainWindow).x, sf::Mouse::getPosition(mainWindow).y, enemyPlayer);
            dataSent = true;
            shootTimer.restart();
        } else {
            enemyPlayer.setVelocity(0, 0);
        }
    }

    //move own player only
    sf::Vector2f movement;
    if (isMainPlayer) {
        movement.x = delay.asSeconds() * mainPlayer.getVelocity().x;
        movement.y = delay.asSeconds() * mainPlayer.getVelocity().y;
        mainPlayer.move(movement);
    }
    else{
        movement.x = delay.asSeconds() * enemyPlayer.getVelocity().x;
        movement.y = delay.asSeconds() * enemyPlayer.getVelocity().y;
        enemyPlayer.move(movement);
    }

    //move all bullets
    for (int x = 0; x < player1Bullets.size(); ++x) {
        movement.x = delay.asSeconds() * player1Bullets[x].getVelocity().x;
        movement.y = delay.asSeconds() * player1Bullets[x].getVelocity().y;
        player1Bullets[x].move(movement);
    }
    for (int x = 0; x < player2Bullets.size(); ++x) {
        movement.x = delay.asSeconds() * player2Bullets[x].getVelocity().x;
        movement.y = delay.asSeconds() * player2Bullets[x].getVelocity().y;
        player2Bullets[x].move(movement);
    }


    //receive information
    struct receivedInfo obtainedData = client.getRecievedData();
    analyzeAndUpdate(obtainedData);

    //send current information
    //if data is not sent for this loop, which happens when bullet is fired
    if (!dataSent) {
        sf::Packet p;
        if (isMainPlayer) {
            p << mainPlayer.getPosition().x << mainPlayer.getPosition().y << 0.0f << 0.0f
              << mainPlayer.getRotation();
        } else {
            p << enemyPlayer.getPosition().x << enemyPlayer.getPosition().y << 0.0f << 0.0f
              << enemyPlayer.getRotation();
        }
        //update server here
        server.update(p);
//            std::cout << "Data sent\n";
    }

    //remove bullet that is off screen
    for (int x = 0; x < player1Bullets.size(); ++x) {
        float posX = player1Bullets[x].getPosition().x;
        float posY = player1Bullets[x].getPosition().y;
        if (posX < -100 or posX > 1500 or posY < -100 or posY > 750) {
            player1Bullets.erase(player1Bullets.begin() + x);
        }
    }
    for (int x = 0; x < player2Bullets.size(); ++x) {
        float posX = player2Bullets[x].getPosition().x;
        float posY = player2Bullets[x].getPosition().y;
        if (posX < -100 or posX > 1500 or posY < -100 or posY > 750) {
            player2Bullets.erase(player2Bullets.begin() + x);
        }
    }
    detectCollision();
}

void MultiPlayerGame::shootBullet(float x, float y, Player &player) {
    Game::shootBullet(x, y, player);
    sf::Packet p = infoToPacket(x,y,player);
    //update server here
    server.update(p);
}

sf::Packet MultiPlayerGame::infoToPacket(float x, float y,Player &player) {
    //own player information
    float playerPositionX;
    float playerPositionY;
    if (isMainPlayer) {
        playerPositionX = mainPlayer.getPosition().x;
        playerPositionY = mainPlayer.getPosition().y;
    }
    else{
        playerPositionX = enemyPlayer.getPosition().x;
        playerPositionY = enemyPlayer.getPosition().y;
    }

    //bullet start positions are player's current positions
    //bullet end positions are x and y

    //send current information
    sf::Packet p;
    p << playerPositionX << playerPositionY << x << y << player.getRotation();
    return p;
}

void MultiPlayerGame::analyzeAndUpdate(struct receivedInfo &receivedData) {
//
    if (isMainPlayer) {
        enemyPlayer.setPosition(receivedData.playerPosition.x, receivedData.playerPosition.y);
        enemyPlayer.setRotation(receivedData.rotation);
    }
    else{
        mainPlayer.setPosition(receivedData.playerPosition.x, receivedData.playerPosition.y);
        mainPlayer.setRotation(receivedData.rotation);
    }

    //if bullet is0 shot
    if (receivedData.bulletEnd.x !=0 and receivedData.bulletEnd.y != 0){
        //effect
        //if it has valid value, shoot a bullet
        if (isMainPlayer) {
            Game::shootBullet(receivedData.bulletEnd.x, receivedData.bulletEnd.y, enemyPlayer);
            client.makeOverRidable(true);
        }
        else{
            Game::shootBullet(receivedData.bulletEnd.x, receivedData.bulletEnd.y, mainPlayer);
            client.makeOverRidable(true);
        }
    }
}
