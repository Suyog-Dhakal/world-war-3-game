//
// Created by udeshya on 3/4/20.
//

#ifndef STAGE3_IPINTERFACE_H
#define STAGE3_IPINTERFACE_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class IpInterface {
    sf::Text ownIpAddress;
    sf::Text USA;
    sf::Text Iran;
    sf::Text EnterIP;
    sf::RectangleShape rect;
    sf::Text back;
    sf::String ip;
    sf::Text ipAddress;
    sf::Font usedFont;
    sf::RenderWindow &mainWindow;
    bool isRunning = true;

    bool isHoveringBack = false;
    bool isHoveringIran = false;
    bool isHoveringUSA = false;

    bool isMainPlayer = false;
    bool isEnemyPlayer = false;

    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Keyboard::Key &key);
public:
    //constructor
    IpInterface(sf::RenderWindow &window);
    void run();
};


#endif //STAGE3_IPINTERFACE_H
