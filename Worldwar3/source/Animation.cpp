//
// Created by Sandesh on 1/23/2020.

#include "Animation.h"

Animation::Animation( sf::Texture* texture, sf::Vector2u imageCount, float switchTime )
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;

    uvRect.width  = texture->getSize().x / (float)imageCount.x;
    uvRect.height = texture->getSize().y / (float)imageCount.y;
}

void Animation::Update(int row, float deltaTime)
{
   // currentImage.y = row;
    totalTime += deltaTime;

    if(totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;
        if(currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
            currentImage.y += 1;
        }
    }

    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;

}

