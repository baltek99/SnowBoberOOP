#pragma once

#include <SFML/Graphics.hpp>

class Visual {
private:
    sf::Sprite sprite;

public:    
    Visual(const sf::Texture& texture_, float scaleX_, float scaleY_);

    sf::Sprite &getSprite();

    sf::Sprite getSprite() const;

    void setTexture(const sf::Texture &texture_);

    float getScaleX() const;

    float getScaleY() const;

    float getRotation() const;

    void setRotation(float rotation_);
};
