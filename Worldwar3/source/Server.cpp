//
// Created by udeshya on 3/2/20.
//

#include "Server.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network/TcpSocket.hpp>

Server::Server(unsigned short port)
{
    m_running = true;
    listenPort(port);
}

int Server::getM_playersConnected() const {
    return m_playersConnected;
}

Server::~Server(){
    m_running = false;
    socket.disconnect();
    m_listener.close();
}
void Server::listenPort(unsigned short port)
{
    if(m_listener.listen(port) == sf::Socket::Done)
    {
        m_selector.add(m_listener);
        m_playersConnected = 0;
        m_dataWaiting = false;
        t0 = std::thread(&Server::receive, this);
        t0.detach();
    }
    else
    {
        listenPort(++port);
    }
}

void Server::receive() {
    while (m_running) {
        while (m_playersConnected == 0) {
            if (m_listener.accept(this->socket) == sf::Socket::Done) {
                ++m_playersConnected;
            }
        }
        if (this->m_dataWaiting){
            if (socket.send(this->m_toSend) != sf::Socket::Done){
//                std::cout << "Could not send data";
            }
            m_mutex.lock();
            this->m_dataWaiting = false;
            m_mutex.unlock();
        }
    }
}

//call this after updating position
void Server::update(sf::Packet &p) {
    this->m_toSend = p;
    m_mutex.lock();
    this->m_dataWaiting = true;
    m_mutex.unlock();
}

void Server::setIsRunning(bool x) {
    m_mutex.lock();
    m_running = x;
    m_mutex.unlock();
}