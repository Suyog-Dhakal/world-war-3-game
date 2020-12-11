//
// Created by udeshya on 3/2/20.
//

#include "Client.h"
#include <iostream>

Client::Client(const sf::IpAddress& ip,unsigned short port, bool isMain)
{
    m_connected=false;
    m_running2=true;
    t1=std::thread(&Client::connection,this,ip,port);
    t1.detach();

    //set default values at first
    if (isMain) {
        receivedData.playerPosition.x = 1200;
        receivedData.playerPosition.y = 600;
    }
    else{
        receivedData.playerPosition.x = 75;
        receivedData.playerPosition.y = 600;
    }
}

Client::~Client() {
    m_running2=false;
    m_socket.disconnect();
}

void Client::connection(const sf::IpAddress& ip, unsigned short port)
{
    unsigned short initPort = port;
    while (!m_connected){
        static int checkLoop=0;
        if (m_socket.connect(ip, port, sf::seconds(15)) != sf::Socket::Done)
        {
            if(checkLoop<2) {
                port++;
                checkLoop++;
            }
            else
            {
                checkLoop = 0;
                port = initPort;
            }
        }
        else {
            m_connected = true;
        }
    }
    while (this->m_running2 && m_connected ) {
        this->receivedData  = recieveData();
    }
}

receivedInfo Client::getRecievedData() {
    return receivedData;
}

receivedInfo& Client::recieveData(){
    m_socket.setBlocking(true);
    sf::Packet Sam;

    if (m_socket.receive(Sam) == sf::Socket::Done and receivedData.canOverRide) {
        Sam >> receivedData.playerPosition.x >> receivedData.playerPosition.y
        >> receivedData.bulletEnd.x >> receivedData.bulletEnd.y >> receivedData.rotation;
//        return a data structure that contains all 3 received information;
        if (receivedData.bulletEnd.x and receivedData.bulletEnd.y){
            receivedData.canOverRide = false;
        }
        return receivedData;
    } else{
//        return a data structure that contains all 3 received information without updating
        receivedData.bulletEnd = sf::Vector2f(0,0);
        return receivedData;
    }
}

void Client::setIsRunning(bool x) {
    m_mutex2.lock();
    m_running2 = x;
    m_mutex2.unlock();
}

void Client::makeOverRidable(bool x) {
    receivedData.canOverRide = x;
}
