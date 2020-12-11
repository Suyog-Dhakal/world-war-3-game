//
// Created by udeshya on 3/2/20.
//

#ifndef STAGE3_CLIENT_H
#define STAGE3_CLIENT_H


#include <thread>
#include <SFML/Network.hpp>
#include <mutex>
#include "Global.h"
#include "mainmenu.h"

class Client {

public:
//    Client(){}
    Client(const sf::IpAddress& ip, unsigned short port, bool isMain);
    void connection(const sf::IpAddress& ip, unsigned short port);
    receivedInfo& recieveData();
    bool isConnected() { return m_connected; }
    virtual ~Client();
    receivedInfo getRecievedData();
    void setIsRunning(bool x);
    void makeOverRidable(bool x);
private:
    sf::TcpSocket m_socket;
    bool m_connected;
    bool m_running2;
    struct receivedInfo receivedData;
    std::thread t1;
    std::mutex m_mutex2;
    int count = 0;
};

#endif //STAGE3_CLIENT_H
