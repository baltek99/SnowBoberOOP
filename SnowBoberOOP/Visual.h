#pragma once
#ifndef VISUAL_H
#define VISUAL_H

#include <SFML/Graphics.hpp>

class Visual
{
private:
    sf::Texture texture;
    int imgWidth;
    int imgHeight;
    float rotation;
public:
    Visual(std::string texturePath, int imgWidth_, int imgHeight_);
    
    Visual(const sf::Texture& texture_, int imgWidth_, int imgHeight_);

    Visual(std::string texturePath, int imgWidth_, int imgHeight_, float rotation_);

    sf::Texture getTexture() const;

    void setTexture(const sf::Texture &texture_);

    int getImgWidth() const;

    int getImgHeight() const;

    float getRotation() const;

    void setRotation(float rotation_);
};
#endif // !VISUAL_H

