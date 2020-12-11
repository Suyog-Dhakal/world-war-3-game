
#ifndef WORLDWAR3_MAINMENU_H
#define WORLDWAR3_MAINMENU_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include <iostream>




class mainmenu {
public:
    mainmenu();

    void Run();

    void ProcessEvents();

    void Update();

    void Draw();

    void DrawMenu();

    void DrawAbout();

    void DrawStopMenu();

    void DrawIPAddress();

    void initializeText(sf::Text &, std::string, int, float, ResourceHolder&, bool);


private:
    ResourceHolder resources;

    sf::RenderWindow window;
    sf::Sprite m_sprite;
    sf::Sprite aboutBG;

    sf::Text m_textsingle;
    sf::Text m_textmulti;
    sf::Text m_textabout;
    sf::Text m_textexit;


    sf::Text m_aboutText;
    sf::Text state_back;

    sf::Text IPAddress_text;
    sf::Text Player1;
    sf::Text Player2;
    sf::Text ip_sentence;

    sf::RectangleShape rectangle;

    sf::Music menuMusic;

    float mouse_y;
    float mouse_x;



    enum State {
        MAINMENU, SINGLEPLAYER, MULTIPLAYER, ABOUT,STOP_MENU
    };
    State state;

    bool isMainPlayer = false; //records if player 1 is selected
    bool isEnemyPlayer = false;
};


#endif //WORLDWAR3_MAINMENU_H
