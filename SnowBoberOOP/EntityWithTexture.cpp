#include "EntityWithTexture.h"

EntityWithTexture::EntityWithTexture(const Position &position_, const Visual &visual_) : Entity(position_), visual(visual_), zIndex(0) {}

Visual EntityWithTexture::getVisual() const {
    return visual;
}

void EntityWithTexture::setVisual(const Visual &visual_) {
    visual = visual_;
}

int EntityWithTexture::getZIndex() const {
    return zIndex;
}

void EntityWithTexture::render(sf::RenderWindow & window) {
    visual.getSprite().setPosition(position.getX(), position.getY());
    window.draw(visual.getSprite());
}

