#include "EntityWithTexture.h"

EntityWithTexture::EntityWithTexture(const Position &position_, const Visual &visual_) : Entity(position_), visual(visual_), zIndex(0) {}

Visual EntityWithTexture::getVisual() const {
    return visual;
}

Visual & EntityWithTexture::getVisual() {
    return visual;
}

void EntityWithTexture::setVisual(const Visual &visual_) {
    visual = visual_;
}

int EntityWithTexture::getZIndex() const {
    return zIndex;
}

void EntityWithTexture::render(sf::RenderWindow & window) {
    sf::Sprite& sprite = visual.getSprite();

    
   sprite.setPosition(position.getX() + sprite.getScale().x * sprite.getLocalBounds().width / 2,
       position.getY() + sprite.getScale().y * sprite.getLocalBounds().height / 2);

    //printf("Pozycja sprite : %f %f \n", visual.getSprite().getPosition().x, visual.getSprite().getPosition().y);

    window.draw(sprite);
    
    
}

