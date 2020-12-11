#include <iostream>
#include "mainmenu.h"
#include "Game.h"
#include <SFML/Network.hpp>
#include <IpInterface.h>
#include "MultiPlayerGame.h"

#define Y_COR 100

mainmenu::mainmenu() : window(sf::VideoMode(1300,650), "WW3") {

    state = State ::MAINMENU;

    m_sprite.setTexture(resources.menuBackground);
    aboutBG.setTexture(resources.backGround);

    state_back.setFillColor(sf::Color::Cyan);
    std::string aboutText = "WORLD WAR III is a 2D game that can be played between two players or with CPU.\n\nThis is developed as a part of the academic project fo Object Oriented Programming.\n\nDevelopers:\n\n\nSANDESH GHIMIRE   075BCT075\nSUYOG DHAKAL   075BCT092\nUDESHYA DHUNGANA   075BCT095";
    initializeText(m_textsingle, "SINGLE PLAYER", 30, 90.0 , resources,   true);
    initializeText(m_textmulti, "MULTI PLAYER", 30, 160.0 , resources,   true);
    initializeText(m_textabout, "ABOUT", 30, 220.0 , resources,  true);
    initializeText(m_textexit, "EXIT", 30, 280.0 , resources, true);

    initializeText(m_aboutText, aboutText, 25, 10 , resources,  false);
    initializeText(state_back, "BACK", 50, 400.0 , resources,  false);

//<<<<<<< HEAD
//    initializeText(m_resume,"RESUME",30,160.0,resources,false);
//    initializeText(m_mainmenu,"MAINMENU",30,220.0,resources,false);
//    std::string myIp = sf::IpAddress(sf::IpAddress::getLocalAddress()).toString();
//    initializeText(IPAddress_text,"Your IP: " + myIp, 30,20,resources,false);
//    initializeText(Player1,"United States",30,250,resources,false);
//    initializeText(Player2,"Iran",30,300,resources,false);
//    initializeText(state_back, "BACK", 50, 400.0 , resources,  false);
//    initializeText(ip_sentence,"Please Enter other's IP:",30,100,resources,false);


    menuMusic.openFromFile("../assets/Sounds/Terminator.wav");
    menuMusic.setLoop(true);
    menuMusic.play();
}




void mainmenu::Run() {
    while (window.isOpen()) {
        ProcessEvents();
        Update();
        Draw();
    }
}

void mainmenu::ProcessEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        switch (event.type) {
            case event.Closed:
                window.close();
                break;
        }

    }
}

void mainmenu::Update() {
    mouse_x = sf::Mouse::getPosition(window).x;
    mouse_y = sf::Mouse::getPosition(window).y;

    if(state == State::MAINMENU)
    {

        if (m_textsingle.getGlobalBounds().contains(mouse_x, mouse_y)) {
            m_textsingle.setFillColor(sf::Color::Red);
        } else {
            m_textsingle.setFillColor(sf::Color::Black);
        }

        if (m_textmulti.getGlobalBounds().contains(mouse_x, mouse_y)) {
            m_textmulti.setFillColor(sf::Color::Red);
        } else {
            m_textmulti.setFillColor(sf::Color::Black);
        }
        if (m_textabout.getGlobalBounds().contains(mouse_x, mouse_y)) {
            m_textabout.setFillColor(sf::Color::Red);
        } else {
            m_textabout.setFillColor(sf::Color::Black);
        }

        if (m_textexit.getGlobalBounds().contains(mouse_x, mouse_y)) {
            m_textexit.setFillColor(sf::Color::Red);
        } else {
            m_textexit.setFillColor(sf::Color::Black);
        }

        //state management
        if (m_textexit.getGlobalBounds().contains(mouse_x, mouse_y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            window.close();

        }
        if (m_textabout.getGlobalBounds().contains(mouse_x, mouse_y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            state = State::ABOUT;

        }
        if (m_textsingle.getGlobalBounds().contains(mouse_x, mouse_y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            state = State::SINGLEPLAYER;
            Game game(window);
            game.run();
            state = State::MAINMENU;
        }
        if (m_textmulti.getGlobalBounds().contains(mouse_x, mouse_y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            state = State::MULTIPLAYER;
            IpInterface ipEnter(window);
            ipEnter.run();
            state = State::MAINMENU;
            menuMusic.stop();
        }

    } else if (state == State::ABOUT)
    {

        if (state_back.getGlobalBounds().contains(mouse_x, mouse_y)) {
            state_back.setFillColor(sf::Color::Red);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                state = State::MAINMENU;
            }
        }
        else {
            state_back.setFillColor(sf::Color::White);
        }
    }
//    else if(state == State::SINGLEPLAYER)
//    {
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
//           {
//                DrawStopMenu();
//           }
//    }
//    else if(state==State::MULTIPLAYER)
//    {
//        //nothing is selected
//        if (!isMainPlayer and !isEnemyPlayer) {
//            if (Player1.getGlobalBounds().contains(mouse_x, mouse_y)) {
//                Player1.setFillColor(sf::Color::Red);
//                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//                    isMainPlayer = true;
//                    isEnemyPlayer = false;
//                }
//            }
//            if (Player2.getGlobalBounds().contains(mouse_x, mouse_y)) {
//                Player2.setFillColor(sf::Color::Red);
//                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//                    isMainPlayer = false;
//                    isEnemyPlayer = true;
//                }
//            }
//            else {
//                Player1.setFillColor(sf::Color::White);
//                Player2.setFillColor(sf::Color::White);
//            }
//        }
//        else if (isMainPlayer and !isEnemyPlayer){
//            if (Player2.getGlobalBounds().contains(mouse_x, mouse_y)){
//                Player2.setFillColor(sf::Color::Yellow);
//                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
//                    isMainPlayer = false;
//                    isEnemyPlayer = true;
//                }
//            }
//            else{
//                Player1.setFillColor(sf::Color::Red);
//                Player2.setFillColor(sf::Color::White);
//            }
//        }
//
//        else if (!isMainPlayer and isEnemyPlayer){
//            if (Player1.getGlobalBounds().contains(mouse_x, mouse_y)){
//                Player1.setFillColor(sf::Color::Yellow);
//                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
//                    isMainPlayer = true;
//                    isEnemyPlayer = false;
//                }
//            }
//            else{
//                Player1.setFillColor(sf::Color::White);
//                Player2.setFillColor(sf::Color::Red);
//            }
//        }
////        if(Player2.getGlobalBounds().contains(mouse_x,mouse_y))
////        {
////            Player2.setFillColor(sf::Color::Red);
////
////        }
////        else{ Player2.setFillColor(sf::Color::White);}
////
//        if(state_back.getGlobalBounds().contains(mouse_x,mouse_y))
//        {
//            state_back.setFillColor(sf::Color::Red);
//            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//                isMainPlayer = false;
//                isEnemyPlayer = false;
//                state = State::MAINMENU;
//            }
//        }
//        else{ state_back.setFillColor(sf::Color::White);}
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
//            //make multiplayer game and run it
//            MultiPlayerGame multiPlayer(window, input_handler.ipAddress, isMainPlayer);
//            multiPlayer.run();
//            isMainPlayer = false;
//            isEnemyPlayer = false;
//            input_handler.ipAddress = "";
//        }
//    }
}

void mainmenu::Draw() {
    window.clear();
    if(state == State::MAINMENU)
        DrawMenu();
    else if (state == State::ABOUT)
        DrawAbout();
    window.display();
}

void mainmenu::DrawMenu() {
    window.draw(m_sprite);
    window.draw(m_textsingle);
    window.draw(m_textmulti);
    window.draw(m_textabout);
    window.draw(m_textexit);
}

void mainmenu::DrawAbout() {
    window.draw(aboutBG);
    window.draw(state_back);
    window.draw(m_aboutText);
}


//void mainmenu::DrawIPAddress() {
//
//    sf::RectangleShape rectangle(sf::Vector2f(120.f, 120.f));
//    rectangle.setSize(sf::Vector2f(300.f, 50.f));
//    rectangle.setPosition(sf::Vector2f(520.f,250.f));
//    rectangle.setFillColor(sf::Color::Transparent);
//    rectangle.setOutlineColor(sf::Color::Red);
//    rectangle.setOutlineThickness(2);
//    input_handler.setPosition(sf::Vector2f(rectangle.getPosition().x + 10, rectangle.getPosition().y + 10));
//    input_handler.setFont(resources.aboutFont);
//    input_handler.setLimit(true, 30);
//    //std::cout << input_handler.getText() << std::endl;
//
//    input_handler.drawTo(window);
//    window.draw(IPAddress_text);
//    window.draw(Player1);
//    window.draw(Player2);
//    window.draw(ip_sentence);
//    window.draw(state_back);
//    window.draw(rectangle);
//}

void mainmenu::initializeText(sf::Text& text, std::string content, int size, float posn, ResourceHolder& resource,  bool isMenu)
{
    text.setString(content);
    if(isMenu == true)
        text.setFont(resource.menuFont);
    else
        text.setFont(resource.aboutFont);
    text.setCharacterSize(size);
    text.setPosition(window.getSize().x/2 - text.getGlobalBounds().width/2, Y_COR + posn);

}

