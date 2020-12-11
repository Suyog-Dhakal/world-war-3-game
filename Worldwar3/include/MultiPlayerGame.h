//
// Created by udeshya on 3/1/20.
//

#ifndef STAGE3_MULTIPLAYERGAME_H
#define STAGE3_MULTIPLAYERGAME_H

#include "Game.h"
#include "Server.h"
#include "Client.h"
#include <SFML/Network.hpp>

class MultiPlayerGame: public Game{
private:
    Server server;
    bool isMainPlayer;
    Client client;
    static void handleComputer();
    void update(sf::Time &delay);
    void shootBullet(float x, float y, Player &player);
    sf::Packet infoToPacket(float x, float y,Player &);
    void analyzeAndUpdate(struct receivedInfo &receivedData);
public:
    MultiPlayerGame(sf::RenderWindow&, const std::string& ip, bool isMainPlayer);
    void run();
};

#endif //STAGE3_MULTIPLAYERGAME_H
