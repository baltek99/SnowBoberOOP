#include "Visual.h"

Visual::Visual(std::string texturePath, int imgWidth_, int imgHeight_) {
    texture.loadFromFile(texturePath);
    imgWidth = imgWidth_;
    imgHeight = imgHeight_;
    rotation = 0;
}

Visual::Visual(const sf::Texture& texture_, int imgWidth_, int imgHeight_) {
    texture = texture_;
    imgWidth = imgWidth_;
    imgHeight = imgHeight_;
    rotation = 0;
}

Visual::Visual(std::string texturePath, int imgWidth_, int imgHeight_, float rotation_) {
    texture.loadFromFile(texturePath);
    imgWidth = imgWidth_;
    imgHeight = imgHeight_;
    rotation = rotation_;
}

sf::Texture Visual::getTexture() const {
    return texture;
}

void Visual::setTexture(const sf::Texture &texture_) {
    texture = texture_;
}

int Visual::getImgWidth() const {
    return imgWidth;
}

int Visual::getImgHeight() const {
    return imgHeight;
}

float Visual::getRotation() const {
    return rotation;
}

void Visual::setRotation(float rotation_) {
    rotation = rotation_;
}
