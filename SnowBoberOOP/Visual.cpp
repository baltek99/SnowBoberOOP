#include "Visual.h"

/*Visual::Visual(std::string texturePath, float scaleX_, float scaleY_) {
    sf::Texture texture;
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    //sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    sprite.setScale(scaleX_, scaleY_);
}*/

Visual::Visual(const sf::Texture& texture, float scaleX_, float scaleY_) {
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);

    sprite.setScale(scaleX_, scaleY_);
}

/*
Visual::Visual(std::string texturePath, float scaleX_, float scaleY_, float rotation_) {
    sf::Texture texture;
    texture.loadFromFile(texturePath);

    sprite.setTexture(texture);
    //sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    sprite.setScale(scaleX_, scaleY_);
    sprite.setRotation(rotation_);
}*/

sf::Sprite & Visual::getSprite() {
    return sprite;
}

sf::Sprite Visual::getSprite() const {
    return sprite;
}

void Visual::setTexture(const sf::Texture &texture_) {
    sprite.setTexture(texture_);
}

float Visual::getScaleX() const {
    return sprite.getScale().x;
}

float Visual::getScaleY() const {
    return sprite.getScale().y;
}

float Visual::getRotation() const {
    return sprite.getRotation();
}

void Visual::setRotation(float rotation_) {
    sprite.setRotation(rotation_);
}
