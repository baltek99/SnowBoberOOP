#pragma once
#ifndef VISUAL_H
#define VISUAL_H

#include <SFML/Graphics.hpp>

class Visual
{
private:
    sf::Sprite sprite;

public:
    Visual(std::string texturePath, float scaleX_, float scaleY_);
    
    Visual(const sf::Texture& texture_, float scaleX_, float scaleY_);

    Visual(std::string texturePath, float scaleX_, float scaleY_, float rotation_);

    sf::Sprite &getSprite();

    sf::Sprite getSprite() const;

    void setTexture(const sf::Texture &texture_);

    float getScaleX() const;

    float getScaleY() const;

    float getRotation() const;

    void setRotation(float rotation_);
};
#endif // !VISUAL_H

