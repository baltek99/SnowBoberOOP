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

void EntityWithTexture::render(/*SpriteBatch batch*/) {
    //batch.draw(
    //    visual.gettexture(),
    //    this.getposition().getx(),
    //    this.getposition().gety(),
    //    visual.getimgwidth() / 2f,
    //    visual.getimgheight() / 2f,
    //    visual.getimgwidth(),
    //    visual.getimgheight(),
    //    1,
    //    1,
    //    visual.getrotation()
    //);
}

