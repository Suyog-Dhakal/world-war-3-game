//
// Created by udeshya on 3/4/20.
//

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <MultiPlayerGame.h>
#include "IpInterface.h"

IpInterface::IpInterface(sf::RenderWindow &pWindow):
    mainWindow(pWindow) {
    usedFont.loadFromFile("../assets/Font/Vermin.ttf");


    ownIpAddress.setFont(usedFont);
    ownIpAddress.setString("Your IP: " + sf::IpAddress::getLocalAddress().toString());
    ownIpAddress.setCharacterSize(24);
    ownIpAddress.setFillColor(sf::Color::White);
    ownIpAddress.setPosition(500, 10);

    USA.setFont(usedFont);
    USA.setString("United States of America");
    USA.setCharacterSize(24);
    USA.setFillColor(sf::Color::White);
    USA.setPosition(100, 400);

    Iran.setFont(usedFont);
    Iran.setString("Iran");
    Iran.setCharacterSize(24);
    Iran.setFillColor(sf::Color::White);
    Iran.setPosition(1000, 400);

    EnterIP.setFont(usedFont);
    EnterIP.setString("Please enter other's IP Address: ");
    EnterIP.setCharacterSize(24);
    EnterIP.setFillColor(sf::Color::White);
    EnterIP.setPosition(400, 150);

    rect.setPosition(450, 200);
    rect.setSize(sf::Vector2f(400, 60));
    rect.setFillColor(sf::Color(204,204,204));

    ipAddress.setFont(usedFont);
    ipAddress.setCharacterSize(24);
    ipAddress.setFillColor(sf::Color::White);
    ipAddress.setPosition(550,215);

    back.setFont(usedFont);
    back.setString("Back");
    back.setCharacterSize(24);
    back.setFillColor(sf::Color::White);
    back.setPosition(600, 600);
}

void IpInterface::run() {
    while (mainWindow.isOpen() and isRunning){
        processEvents();
        update();
        render();
    }
}

void IpInterface::processEvents() {
    sf::Event evt{};
    while (mainWindow.pollEvent(evt)) {
        switch (evt.type) {
            case (sf::Event::Closed):
                mainWindow.close();
                break;
            case (sf::Event::KeyPressed):
                handlePlayerInput(evt.key.code);
                break;
            case(sf::Event::TextEntered):
                if((evt.text.unicode>=48 && evt.text.unicode<=57)||(evt.text.unicode==46))
                {
                    ip+=evt.text.unicode;
                    ipAddress.setString(ip);
                }else if(evt.text.unicode==8 && !ip.isEmpty())
                {
                    ip.erase(ip.getSize()-1,1);
                    ipAddress.setString(ip);
                }
                break;
        }
    }
}

void IpInterface::update(){
    if (!isMainPlayer and !isEnemyPlayer){
        if (USA.getGlobalBounds().contains(sf::Mouse::getPosition(mainWindow).x, sf::Mouse::getPosition(mainWindow).y)){
            isHoveringUSA = true;
            isHoveringIran = false;
            isHoveringBack = false;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                isMainPlayer = true;
                isEnemyPlayer = false;
            }
        }
        else if (Iran.getGlobalBounds().contains(sf::Mouse::getPosition(mainWindow).x, sf::Mouse::getPosition(mainWindow).y)){
            isHoveringUSA = false;
            isHoveringIran = true;
            isHoveringBack = false;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                isEnemyPlayer = true;
                isMainPlayer = false;
            }
        }
        else if (back.getGlobalBounds().contains(sf::Mouse::getPosition(mainWindow).x, sf::Mouse::getPosition(mainWindow).y)){
            isHoveringIran = false;
            isHoveringUSA = false;
            isHoveringBack = true;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                isRunning = false;
            }
        }
        else {
            isHoveringUSA = false;
            isHoveringIran = false;
            isHoveringBack = false;
        }
    }

    else if (isMainPlayer and !isEnemyPlayer){
        if (Iran.getGlobalBounds().contains(sf::Mouse::getPosition(mainWindow).x, sf::Mouse::getPosition(mainWindow).y)){
            isHoveringIran = true;
            isHoveringUSA = false;
            isHoveringBack = false;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                isMainPlayer = false;
                isEnemyPlayer = true;
            }
        }
        else if (back.getGlobalBounds().contains(sf::Mouse::getPosition(mainWindow).x, sf::Mouse::getPosition(mainWindow).y)){
            isHoveringIran = false;
            isHoveringUSA = false;
            isHoveringBack = true;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                isRunning = false;
            }
        }
        else{
            isHoveringBack = false;
            isHoveringUSA = false;
            isHoveringIran = false;
        }
    }
    else if (!isMainPlayer and isEnemyPlayer){
        if (USA.getGlobalBounds().contains(sf::Mouse::getPosition(mainWindow).x, sf::Mouse::getPosition(mainWindow).y)){
            isHoveringIran = false;
            isHoveringUSA = true;
            isHoveringBack = false;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                isMainPlayer = true;
                isEnemyPlayer = false;
            }
        }
        else if (back.getGlobalBounds().contains(sf::Mouse::getPosition(mainWindow).x, sf::Mouse::getPosition(mainWindow).y)){
            isHoveringIran = false;
            isHoveringUSA = false;
            isHoveringBack = true;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                isRunning = false;
            }
        }
        else{
            isHoveringIran = false;
            isHoveringUSA = false;
            isHoveringBack= false;
        }
    }


}

void IpInterface::render() {
    mainWindow.clear(sf::Color::Black);
    mainWindow.draw(ownIpAddress);
    mainWindow.draw(EnterIP);
    mainWindow.draw(rect);
    mainWindow.draw(ipAddress);

    USA.setFillColor(sf::Color::White);
    Iran.setFillColor(sf::Color::White);
    back.setFillColor(sf::Color::White);

    if (!isMainPlayer and !isEnemyPlayer){
        if (isHoveringUSA){
            USA.setFillColor(sf::Color::Yellow);
        }
        else if (isHoveringIran){
            Iran.setFillColor(sf::Color::Yellow);
        }
        else if (isHoveringBack){
            back.setFillColor(sf::Color::Yellow);
        }
    }
    else if (isMainPlayer and !isEnemyPlayer){
        USA.setFillColor(sf::Color::Red);
        if (isHoveringIran){
            Iran.setFillColor(sf::Color::Yellow);
        }
        else if (isHoveringBack){
            back.setFillColor(sf::Color::Yellow);
        }
    }
    else if (!isMainPlayer and isEnemyPlayer){
        Iran.setFillColor(sf::Color::Red);
        if (isHoveringUSA){
            USA.setFillColor(sf::Color::Yellow);
        }
        else if (isHoveringBack){
            back.setFillColor(sf::Color::Yellow);
        }
    }
    mainWindow.draw(Iran);
    mainWindow.draw(USA);
    mainWindow.draw(back);
    mainWindow.display();
}

void IpInterface::handlePlayerInput(sf::Keyboard::Key &key) {
    if (key == sf::Keyboard::Return){
        if (!ip.isEmpty() and (isMainPlayer or isEnemyPlayer)){
            MultiPlayerGame game(mainWindow, this->ip.toAnsiString(), isMainPlayer);
            game.run();
            isRunning = false;
        }
    }
}
