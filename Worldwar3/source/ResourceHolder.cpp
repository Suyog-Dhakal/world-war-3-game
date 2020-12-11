#include "ResourceHolder.h"

ResourceHolder::ResourceHolder() {
    //load textures from corresponding files
//    Textures
    backGround.loadFromFile("../assets/Texture/1.jpg");
    player.loadFromFile("../assets/Texture/tank3.png");
    bullet.loadFromFile("../assets/Texture/Bullet.png");
    menuBackground.loadFromFile("../assets/Texture/BG_ww3_3.png");
    explosion.loadFromFile("../assets/Texture/t2.png");



//    Fonts
    menuFont.loadFromFile("../assets/Font/Vermin.ttf");
    aboutFont.loadFromFile("../assets/Font/aboutfont.ttf");
    gameOverFont.loadFromFile("../assets/Font/Tarrget.otf");


//    Sounds
    fireBuffer.loadFromFile("../assets/Sounds/Cannon.wav");
}