
#include "Game.h"
#include "Animation.h"
#include <math.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <sstream>

int getRandomNumber() {
    int num = std::rand() % 101;
    if (num < 33) {
        return -1;
    } else if (num >= 33 and num < 66) {
        return 1;
    } else {
        return 0;
    }
}

//game constructor, here we create main window, our main player and load texture to our background->
//sprite
Game::Game(sf::RenderWindow &pWindow) :
        mainWindow(pWindow),
        mainPlayer(sf::Vector2f(75, 600), sf::Vector2f(), resources.player, 1),
        enemyPlayer(sf::Vector2f(1200, 600), sf::Vector2f(), resources.player, 2){
        backgroundSprite.setTexture(resources.backGround);
        fire.setBuffer(resources.fireBuffer);
        shootTimer.restart();
        computerClock.restart();
}

//process events from user's input, i.e. keyboard button pressed, or mouse clicked
void Game::processEvents() {
    sf::Event evt;
    while (mainWindow.pollEvent(evt)) {
        switch (evt.type) {
            case (sf::Event::Closed):
                mainWindow.close();
                break;

        }
    }
}


void Game::update(sf::Time &delay) {

    elapsed = shootTimer.getElapsedTime();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        mainPlayer.rotatePlayer(sf::Vector2i(0,1));
        mainPlayer.setVelocity(mainPlayer.getVelocity().x, -mainPlayer.getSpeed());
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        mainPlayer.rotatePlayer(sf::Vector2i(0,-1));
        mainPlayer.setVelocity(mainPlayer.getVelocity().x, mainPlayer.getSpeed());
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        mainPlayer.rotatePlayer(sf::Vector2i(-1,0));
        mainPlayer.setVelocity(-mainPlayer.getSpeed(), mainPlayer.getVelocity().y);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        mainPlayer.rotatePlayer(sf::Vector2i(1,0));
        mainPlayer.setVelocity(mainPlayer.getSpeed(), mainPlayer.getVelocity().y);
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  &&  elapsed.asSeconds() > 1)
    {
        shootBullet(sf::Mouse::getPosition(mainWindow).x , sf::Mouse::getPosition(mainWindow).y , mainPlayer);
        shootTimer.restart();
    }

    else {
        mainPlayer.setVelocity(0, 0);
    }

    //make player move by 1 frame
    sf::Vector2f movement;
    movement.x = delay.asSeconds() * mainPlayer.getVelocity().x;
    movement.y = delay.asSeconds() * mainPlayer.getVelocity().y;
    mainPlayer.move(movement);


    if(computerClock.getElapsedTime().asSeconds() > 2)
    {
        int y = getRandomNumber() * -1;
        int x = getRandomNumber();

        enemyPlayer.setVelocity(enemyPlayer.getSpeed() * x, enemyPlayer.getSpeed() * y);

        computerClock.restart();
    }
    sf::Vector2f cpuMovement;
    cpuMovement.x = delay.asSeconds() * enemyPlayer.getVelocity().x;
    cpuMovement.y = delay.asSeconds() * enemyPlayer.getVelocity().y;
    enemyPlayer.move(cpuMovement);


    //remove bullets from 'bullets' vector if it's off screen
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
    //move all bullets by 1 frame
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
    detectCollision();
}


void Game::render() {
    mainWindow.clear();
    //draw background sprite
    mainWindow.draw(backgroundSprite);
    //draw bullets
    for (auto &bullet : player1Bullets) {
        bullet.draw(mainWindow);
    }
    for (auto &bullet: player2Bullets) {
        bullet.draw(mainWindow);
    }
    //draw players
    mainPlayer.draw(mainWindow);
    enemyPlayer.draw(mainWindow);

    displayText(mainWindow);
    mainWindow.display();
}

//this function calls processEvents(), update() and render() function
void Game::run() {
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
//creates a bullet on key press, gives it appropriate velocity and appends to 'bullets' vector
void Game::shootBullet(float x, float y, Player &player) {
    sf::Vector2f v;
    v.x = x - player.getPosition().x ;
    v.y = y - player.getPosition().y ;

    player.rotate(v);

    double h = hypot(v.x, v.y);
    v.x = v.x * 1500 / h;
    v.y = v.y * 1500 / h;

    fire.play();

    Bullet b(player.getPosition() + sf::Vector2f(0, -0), v, resources.bullet);
    b.rotate(v);
    if (player.getId() == 1) {
        player1Bullets.push_back(b);
    } else {
        player2Bullets.push_back(b);
    }

}

void Game::handleComputer() {
    sf::Vector2f v;
    v = mainPlayer.getPosition() - enemyPlayer.getPosition();
    enemyPlayer.rotate(v);

    double h = hypot(v.x, v.y);
    v.x = v.x * 1000 / h;
    v.y = v.y * 1000 / h;
    Bullet b(enemyPlayer.getPosition() + sf::Vector2f(20, 20), v, resources.bullet);
    b.rotate(v);
    player2Bullets.push_back(b);
    fire.play();
}

void Game::detectCollision() {
    std::vector<int> toDelete;
    for (int x = 0; x < player1Bullets.size(); ++x) {
        if (player1Bullets[x].getSprite().getGlobalBounds().intersects(enemyPlayer.getSprite().getGlobalBounds())) {
            enemyPlayer.decreaseHealth();
            toDelete.push_back(x);
        }
    }
    for (int &x:toDelete) {
        player1Bullets.erase(player1Bullets.begin() + x);
    }
    std::vector<int> toDelete2;
    for (int x = 0; x < player2Bullets.size(); ++x) {
        if (player2Bullets[x].getSprite().getGlobalBounds().intersects(mainPlayer.getSprite().getGlobalBounds())) {
            mainPlayer.decreaseHealth();
            toDelete2.push_back(x);
        }
    }
    for (int &x:toDelete2) {
        player2Bullets.erase(player2Bullets.begin() + x);
    }
}

void Game::displayText(sf::RenderWindow &window) {
    std::stringstream ss;
    ss << mainPlayer.getHealth();
    std::string player1Health;
    ss >> player1Health;
    player1Health = "Health : " + player1Health;
    sf::Text player1HealthInfo;
    player1HealthInfo.setFont(resources.menuFont);
    player1HealthInfo.setString(player1Health);
    player1HealthInfo.setCharacterSize(15);
    player1HealthInfo.setFillColor(sf::Color(sf::Color::White));
    player1HealthInfo.setOrigin(player1HealthInfo.getPosition().x/2, player1HealthInfo.getPosition().y/2);
    player1HealthInfo.setPosition(mainPlayer.getPosition().x  - 60 , mainPlayer.getPosition().y - 80);
    window.draw(player1HealthInfo);


    std::stringstream ss2;
    ss2 << enemyPlayer.getHealth();
    std::string player2Health;
    ss2 >> player2Health;
    player2Health = "Health: " + player2Health;
    sf::Text player2HealthInfo;
    player2HealthInfo.setFont(resources.menuFont);
    player2HealthInfo.setString(player2Health);
    player2HealthInfo.setCharacterSize(15);
    player2HealthInfo.setFillColor(sf::Color(sf::Color::White));
    player2HealthInfo.setOrigin(player2HealthInfo.getPosition().x/2, player2HealthInfo.getPosition().y/2);
    player2HealthInfo.setPosition(enemyPlayer.getPosition().x  - 60 , enemyPlayer.getPosition().y -80);
    window.draw(player2HealthInfo);
}

void Game::displayGameOver(int mPHealth, int ePHealth) {

    sf::Text end;
    end.setFont(resources.gameOverFont);
    end.setFillColor(sf::Color::White);
    end.setPosition(330,200);
    end.setCharacterSize(80);
    end.setString("GAME - OVER");

    sf::Text winString;
    winString.setFont(resources.gameOverFont);
    winString.setFillColor(sf::Color::White);
    winString.setPosition(380,310);
    winString.setCharacterSize(50);


    sf::Clock clk;
    sf::Clock timer;
    timer.restart();

    Animation animation(&resources.explosion, sf::Vector2u(8, 8), 0.1f);
    sf::Sprite bomb;
    bomb.setTexture(resources.explosion);

    if(mPHealth == 0)
    {
        mainPlayer.changeColor(sf::Color::Black);
        bomb.setPosition(mainPlayer.getPosition().x - 90 , mainPlayer.getPosition().y - 105);
        winString.setString("Iran wins");
    }

    else if(ePHealth == 0)
    {
        enemyPlayer.changeColor(sf::Color::Black);
        winString.setString("United States wins");
        bomb.setPosition(enemyPlayer.getPosition().x - 90 , enemyPlayer.getPosition().y - 105);
    }


    while (mainWindow.isOpen()) {

        deltaTime = clk.restart().asSeconds();

        if(timer.getElapsedTime().asSeconds() > sf::seconds(5).asSeconds()) {
            break;
        }

        animation.Update(0, deltaTime);
        bomb.setTextureRect(animation.uvRect);

        mainWindow.clear();
        mainWindow.draw(backgroundSprite);
        mainPlayer.draw(mainWindow);
        enemyPlayer.draw(mainWindow);
        mainWindow.draw(bomb);
        mainWindow.draw(winString);
        mainWindow.draw(end);
        mainWindow.display();
    }



}